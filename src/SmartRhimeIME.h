#pragma once
#include <windows.h>
#include <string>
#include <map>
#include <vector>

// 智能拼音输入法核心类
class SmartRhimeIME {
private:
    // 词库数据结构
    std::map<std::string, std::vector<std::pair<std::string, int>>> m_pinyinToWords;
    std::map<std::string, std::vector<std::string>> m_pinyinDict;
    std::string m_userDictPath;

public:
    SmartRhimeIME();
    ~SmartRhimeIME() = default;

    // 初始化基础拼音字典
    void initPinyinDict();

    // 加载所有词库
    void loadDictionaries();

    // 加载单个词库文件
    void loadDictionary(const std::string& filePath);

    // 加载用户词库
    void loadUserDictionary();

    // 保存用户词库
    void saveUserDictionary();

    // 添加用户词语
    void addUserWord(const std::string& word, int freq = 2000);

    // 获取汉字的拼音
    std::string getCharPinyin(char ch);

    // 获取词语的拼音
    std::string getWordPinyin(const std::string& word);

    // 根据拼音查找候选词
    std::vector<std::string> findCandidates(const std::string& pinyin);
};

// Windows API 相关函数声明
EXTERN_C __declspec(dllexport) HRESULT WINAPI ImmInitialize(HIMC hIMC);
EXTERN_C __declspec(dllexport) HRESULT WINAPI ImmConfigureIME(HWND hwndOwner, DWORD dwAction, LPVOID lpv);
EXTERN_C __declspec(dllexport) HRESULT WINAPI ImmProcessKey(HIMC hIMC, UINT vKey, BOOL fDown, DWORD dwFlags);