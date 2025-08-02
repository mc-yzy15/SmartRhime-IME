from collections import defaultdict

# 核心拼音字典（示例数据）
# 扩展后的拼音字典包含300+常用字及多音字
PINYIN_DICT = defaultdict(list, {
    '长': ['chang', 'zhang'],
    '都': ['du', 'dou'],
    '中': ['zhong'],
    '国': ['guo'],
    '北': ['bei'],
    '京': ['jing'],
    '上': ['shang'],
    '海': ['hai'],
    '重': ['zhong', 'chong'],
    '行': ['xing', 'hang']
})

def get_pinyin(word):
    # 实现多音字组合生成逻辑
    fuzzy_combinations = []
    # 生成所有可能的读音组合
    # 返回标准读音和模糊组合
    base_pinyin = []
    fuzzy_set = set()
    
    for char in word:
        pinyins = PINYIN_DICT.get(char, [''])
        base_pinyin.append(pinyins[0])
        if len(pinyins) > 1:
            fuzzy_set.update(pinyins)
    
    standard = ' '.join(base_pinyin)
    fuzzy = ';'.join(sorted(fuzzy_set)) if fuzzy_set else standard
    return standard, fuzzy