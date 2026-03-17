#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winhttp.h>
#include <string>
#include <sstream>
#pragma comment(lib, "winhttp.lib")

namespace KeyAuth {

    // Application credentials
    static const std::wstring name    = L"levelup-cs2";
    static const std::wstring ownerid = L"WYOFQ63Axg";
    static const std::wstring secret  = L"262f66fef606a0d389383628b4ea4e87eda77f31d4745da5efd15a11104a400b";
    static const std::wstring version = L"1.0";
    static const std::wstring apiurl  = L"keyauth.win";

    // Simple JSON field extractor — no external library needed
    inline std::string json_get(const std::string& json, const std::string& key) {
        std::string search = "\"" + key + "\":";
        size_t pos = json.find(search);
        if (pos == std::string::npos) return "";
        pos += search.size();
        // skip whitespace
        while (pos < json.size() && (json[pos] == ' ' || json[pos] == '\t')) pos++;
        if (pos >= json.size()) return "";

        if (json[pos] == '"') {
            // string value
            pos++;
            size_t end = json.find('"', pos);
            if (end == std::string::npos) return "";
            return json.substr(pos, end - pos);
        } else {
            // bool / number
            size_t end = json.find_first_of(",}\n", pos);
            if (end == std::string::npos) end = json.size();
            return json.substr(pos, end - pos);
        }
    }

    inline std::string post(const std::wstring& host, const std::wstring& path, const std::string& body) {
        std::string response;

        HINTERNET hSession = WinHttpOpen(L"KeyAuth/1.0",
            WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
            WINHTTP_NO_PROXY_NAME,
            WINHTTP_NO_PROXY_BYPASS, 0);
        if (!hSession) return "";

        HINTERNET hConnect = WinHttpConnect(hSession, host.c_str(), INTERNET_DEFAULT_HTTPS_PORT, 0);
        if (!hConnect) { WinHttpCloseHandle(hSession); return ""; }

        HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"POST", path.c_str(),
            NULL, WINHTTP_NO_REFERER,
            WINHTTP_DEFAULT_ACCEPT_TYPES,
            WINHTTP_FLAG_SECURE);
        if (!hRequest) { WinHttpCloseHandle(hConnect); WinHttpCloseHandle(hSession); return ""; }

        std::wstring headers = L"Content-Type: application/x-www-form-urlencoded";
        BOOL sent = WinHttpSendRequest(hRequest,
            headers.c_str(), (DWORD)headers.size(),
            (LPVOID)body.c_str(), (DWORD)body.size(),
            (DWORD)body.size(), 0);

        if (sent) {
            WinHttpReceiveResponse(hRequest, NULL);
            DWORD dwSize = 0;
            do {
                dwSize = 0;
                WinHttpQueryDataAvailable(hRequest, &dwSize);
                if (dwSize == 0) break;
                std::string chunk(dwSize, '\0');
                DWORD dwDownloaded = 0;
                WinHttpReadData(hRequest, &chunk[0], dwSize, &dwDownloaded);
                chunk.resize(dwDownloaded);
                response += chunk;
            } while (dwSize > 0);
        }

        WinHttpCloseHandle(hRequest);
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        return response;
    }

    // URL-encode a wide string to a narrow percent-encoded string
    inline std::string url_encode(const std::wstring& ws) {
        // Convert wstring to UTF-8 first
        int len = WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), -1, nullptr, 0, nullptr, nullptr);
        std::string s(len - 1, '\0');
        WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), -1, &s[0], len, nullptr, nullptr);

        std::ostringstream out;
        for (unsigned char c : s) {
            if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
                out << c;
            } else {
                out << '%' << std::uppercase << std::hex << (int)c;
            }
        }
        return out.str();
    }

    // Generate a unique, persistent HWID (at least 20 chars for KeyAuth)
    inline std::string get_hwid() {
        char compName[MAX_PATH];
        DWORD size = sizeof(compName);
        GetComputerNameA(compName, &size);

        DWORD volSerial = 0;
        GetVolumeInformationA("C:\\", NULL, 0, &volSerial, NULL, NULL, NULL, 0);

        std::stringstream ss;
        ss << "LUL-" << compName << "-" << std::hex << volSerial << "-LUL-SECURE-HWID";
        std::string hwid = ss.str();
        
        // Ensure it is at least 20 characters
        while (hwid.length() < 24) {
            hwid += "0";
        }
        return hwid;
    }

    // -----------------------------------------------------------------
    // Main entry point: call this with the user's license key.
    // Returns true if KeyAuth accepts the key, false otherwise.
    // -----------------------------------------------------------------
    inline bool initialize(const std::string& key) {
        std::string hwid = get_hwid();
        // Build body
        std::string body =
            "type=init"
            "&ver="    + url_encode(version)  +
            "&name="   + url_encode(name)     +
            "&ownerid="+ url_encode(ownerid)  +
            "&secret=" + url_encode(secret);

        std::string init_resp = post(apiurl, L"/api/1.3/", body);
        if (init_resp.empty()) {
            std::cout << "[KeyAuth] Could not reach auth server. Check your internet connection." << std::endl;
            return false;
        }

        std::string success = json_get(init_resp, "success");
        if (success != "true") {
            std::string msg = json_get(init_resp, "message");
            std::cout << "[KeyAuth] Init failed: " << msg << std::endl;
            return false;
        }

        std::string sessionid = json_get(init_resp, "sessionid");

        // Now authenticate the key
        // Convert key to wstring for url_encode
        std::wstring wkey(key.begin(), key.end());
        std::string auth_body =
            "type=license"
            "&key="       + url_encode(wkey)      +
            "&sessionid=" + url_encode(std::wstring(sessionid.begin(), sessionid.end())) +
            "&name="      + url_encode(name)       +
            "&ownerid="   + url_encode(ownerid)    +
            "&hwid="      + url_encode(std::wstring(hwid.begin(), hwid.end()));

        std::string auth_resp = post(apiurl, L"/api/1.3/", auth_body);
        if (auth_resp.empty()) {
            std::cout << "[KeyAuth] Auth server did not respond." << std::endl;
            return false;
        }

        std::string auth_success = json_get(auth_resp, "success");
        if (auth_success != "true") {
            std::string msg = json_get(auth_resp, "message");
            std::cout << "[KeyAuth] " << msg << std::endl;
            return false;
        }

        return true;
    }

} // namespace KeyAuth
