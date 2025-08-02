#include <windows.h>
#include <imm.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

// 智能拼音输入法核心实现
class SmartRhimeIME {
private:
    // 词库数据结构
    std::map<std::string, std::vector<std::pair<std::string, int>>> m_pinyinToWords;
    std::map<std::string, std::vector<std::string>> m_pinyinDict;
    std::string m_userDictPath;

public:
    SmartRhimeIME() : m_userDictPath("userdict.dat") {
        // 初始化拼音字典
    initPinyinDict();

    // 加载词库
    loadDictionaries();
    }

    // 初始化基础拼音字典
    void SmartRhimeIME::initPinyinDict() {
        // 完整拼音字典
        m_pinyinDict["一"] = {"yi"};
        m_pinyinDict["丁"] = {"ding"};
        m_pinyinDict["七"] = {"qi"};
        m_pinyinDict["八"] = {"ba"};
        m_pinyinDict["九"] = {"jiu"};
        m_pinyinDict["十"] = {"shi"};
        m_pinyinDict["百"] = {"bai"};
        m_pinyinDict["千"] = {"qian"};
        m_pinyinDict["万"] = {"wan"};
        m_pinyinDict["亿"] = {"yi"};
        m_pinyinDict["个"] = {"ge"};
        m_pinyinDict["十"] = {"shi"};
        m_pinyinDict["百"] = {"bai"};
        m_pinyinDict["千"] = {"qian"};
        m_pinyinDict["万"] = {"wan"};
        m_pinyinDict["亿"] = {"yi"};
        m_pinyinDict["长"] = {"chang", "zhang"};
        m_pinyinDict["都"] = {"du", "dou"};
        m_pinyinDict["中"] = {"zhong"};
        m_pinyinDict["国"] = {"guo"};
        m_pinyinDict["北"] = {"bei"};
        m_pinyinDict["京"] = {"jing"};
        m_pinyinDict["上"] = {"shang"};
        m_pinyinDict["海"] = {"hai"};
        m_pinyinDict["重"] = {"zhong", "chong"};
        m_pinyinDict["行"] = {"xing", "hang"};
        m_pinyinDict["人"] = {"ren"};
        m_pinyinDict["口"] = {"kou"};
        m_pinyinDict["手"] = {"shou"};
        m_pinyinDict["足"] = {"zu"};
        m_pinyinDict["目"] = {"mu"};
        m_pinyinDict["耳"] = {"er"};
        m_pinyinDict["鼻"] = {"bi"};
        m_pinyinDict["舌"] = {"she"};
        m_pinyinDict["心"] = {"xin"};
        m_pinyinDict["肝"] = {"gan"};
        m_pinyinDict["脾"] = {"pi"};
        m_pinyinDict["肺"] = {"fei"};
        m_pinyinDict["肾"] = {"shen"};
        m_pinyinDict["金"] = {"jin"};
        m_pinyinDict["木"] = {"mu"};
        m_pinyinDict["水"] = {"shui"};
        m_pinyinDict["火"] = {"huo"};
        m_pinyinDict["土"] = {"tu"};
        m_pinyinDict["东"] = {"dong"};
        m_pinyinDict["南"] = {"nan"};
        m_pinyinDict["西"] = {"xi"};
        m_pinyinDict["北"] = {"bei"};
        m_pinyinDict["中"] = {"zhong"};
        m_pinyinDict["天"] = {"tian"};
        m_pinyinDict["地"] = {"di"};
        m_pinyinDict["日"] = {"ri"};
        m_pinyinDict["月"] = {"yue"};
        m_pinyinDict["星"] = {"xing"};
        m_pinyinDict["风"] = {"feng"};
        m_pinyinDict["云"] = {"yun"};
        m_pinyinDict["雨"] = {"yu"};
        m_pinyinDict["雪"] = {"xue"};
        m_pinyinDict["雷"] = {"lei"};
        m_pinyinDict["电"] = {"dian"};
        // 可以继续添加更多汉字的拼音
    }

    // 加载所有词库
    void loadDictionaries() {
        // 加载基础词库
        loadDictionary("dict\THUOCL_IT.txt");
        loadDictionary("dict\THUOCL_animal.txt");
        // 可以继续加载其他词库

        // 加载用户词库
        loadUserDictionary();
    }

    // 加载单个词库文件
    void loadDictionary(const std::string& filePath) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "无法打开词库文件: " << filePath << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#') continue;

            size_t tabPos = line.find('\t');
            if (tabPos == std::string::npos) continue;

            std::string word = line.substr(0, tabPos);
            int freq = std::stoi(line.substr(tabPos + 1));

            // 获取词语的拼音
            std::string pinyin = getWordPinyin(word);
            if (!pinyin.empty()) {
                m_pinyinToWords[pinyin].push_back({word, freq});
            }
        }

        file.close();
    }

    // 加载用户词库
    void loadUserDictionary() {
        std::ifstream file(m_userDictPath);
        if (!file.is_open()) {
            // 如果用户词库不存在，创建一个空文件
            std::ofstream newFile(m_userDictPath);
            newFile.close();
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#') continue;

            size_t tabPos = line.find('	');
            if (tabPos == std::string::npos) continue;

            std::string word = line.substr(0, tabPos);
            int freq = std::stoi(line.substr(tabPos + 1));

            // 获取词语的拼音
            std::string pinyin = getWordPinyin(word);
            if (!pinyin.empty()) {
                m_pinyinToWords[pinyin].push_back({word, freq});
            }
        }

        file.close();
    }

    // 保存用户词库
    void saveUserDictionary() {
        std::ofstream file(m_userDictPath);
        if (!file.is_open()) {
            std::cerr << "无法打开用户词库文件进行写入: " << m_userDictPath << std::endl;
            return;
        }

        // 写入用户词库头部信息
        file << "# 用户词库 - 由SmartRhime输入法自动生成\n";

        // 遍历所有词语
        for (const auto& entry : m_pinyinToWords) {
            for (const auto& pair : entry.second) {
                // 只保存用户添加的词语（可以通过词频阈值判断）
                if (pair.second > 1000) {
                    file << pair.first << '\t' << pair.second << '\n';
                }
            }
        }

        file.close();
    }

    // 添加用户词语
    void addUserWord(const std::string& word, int freq = 2000) {
        std::string pinyin = getWordPinyin(word);
        if (!pinyin.empty()) {
            // 检查词语是否已存在
            auto& words = m_pinyinToWords[pinyin];
            for (auto& pair : words) {
                if (pair.first == word) {
                    // 更新词频
                    pair.second = std::max(pair.second + 10, freq);
                    saveUserDictionary();
                    return;
                }
            }

            // 添加新词
            words.push_back({word, freq});
            saveUserDictionary();
        }
    }

    // 获取汉字的拼音
    std::string getCharPinyin(char ch) {
        std::string charStr(1, ch);
        if (m_pinyinDict.find(charStr) != m_pinyinDict.end()) {
            // 返回第一个拼音（默认读音）
            return m_pinyinDict[charStr][0];
        }
        return "";
    }

    // 获取词语的拼音
    std::string getWordPinyin(const std::string& word) {
        std::string pinyin;
        for (char ch : word) {
            std::string charPinyin = getCharPinyin(ch);
            if (charPinyin.empty()) {
                return "";
            }
            if (!pinyin.empty()) {
                pinyin += ";";
            }
            pinyin += charPinyin;
        }
        return pinyin;
    }

    // 计算Levenshtein距离（字符串相似度）
    int levenshteinDistance(const std::string& s1, const std::string& s2) {
        const int m = s1.length();
        const int n = s2.length();

        // 创建距离矩阵
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

        // 初始化边界
        for (int i = 0; i <= m; ++i) {
            dp[i][0] = i;
        }
        for (int j = 0; j <= n; ++j) {
            dp[0][j] = j;
        }

        // 填充矩阵
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                int cost = (s1[i-1] == s2[j-1]) ? 0 : 1;
                dp[i][j] = std::min({dp[i-1][j] + 1,        // 删除
                                     dp[i][j-1] + 1,        // 插入
                                     dp[i-1][j-1] + cost}); // 替换
            }
        }

        return dp[m][n];
    }

    // 智能拼音纠错
    std::string correctPinyin(const std::string& pinyin) {
        // 如果拼音已经存在于词库中，直接返回
        if (m_pinyinToWords.find(pinyin) != m_pinyinToWords.end()) {
            return pinyin;
        }

        // 查找最相似的拼音
        std::string bestMatch;
        int minDistance = INT_MAX;

        for (const auto& entry : m_pinyinToWords) {
            const std::string& candidate = entry.first;
            int distance = levenshteinDistance(pinyin, candidate);

            // 如果找到更相似的拼音，更新最佳匹配
            if (distance < minDistance) {
                minDistance = distance;
                bestMatch = candidate;
            }
        }

        // 只有当距离足够小时才返回纠错结果
        return (minDistance <= 2) ? bestMatch : pinyin;
    }

    // 根据拼音查找候选词（带智能纠错）
    std::vector<std::string> findCandidates(const std::string& pinyin) {
        std::vector<std::string> candidates;

        // 尝试直接查找
        if (m_pinyinToWords.find(pinyin) != m_pinyinToWords.end()) {
            // 按词频排序
            std::vector<std::pair<std::string, int>>& words = m_pinyinToWords[pinyin];
            std::sort(words.begin(), words.end(), [](const auto& a, const auto& b) {
                return a.second > b.second;
            });

            // 提取排好序的词语
            for (const auto& pair : words) {
                candidates.push_back(pair.first);
            }
        } else if (!candidates.empty()) {
            // 如果没有找到，尝试智能纠错
            std::string correctedPinyin = correctPinyin(pinyin);
            if (correctedPinyin != pinyin && m_pinyinToWords.find(correctedPinyin) != m_pinyinToWords.end()) {
                // 按词频排序
                std::vector<std::pair<std::string, int>>& words = m_pinyinToWords[correctedPinyin];
                std::sort(words.begin(), words.end(), [](const auto& a, const auto& b) {
                    return a.second > b.second;
                });

                // 提取排好序的词语
                for (const auto& pair : words) {
                    candidates.push_back(pair.first);
                }
            }
        }

        return candidates;
    }
};

// Windows API 相关函数
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved) {
    switch (dwReason) {
    case DLL_PROCESS_ATTACH:
        // 初始化输入法
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

// 输入法入口函数
EXTERN_C __declspec(dllexport) HRESULT WINAPI ImmInitialize(HIMC hIMC) {
    // 初始化IMM上下文
    return S_OK;
}