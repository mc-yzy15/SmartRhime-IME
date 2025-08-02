import os
import argparse
from collections import defaultdict

def merge_dicts(input_dir, output_file):
    import jieba
    from scripts.pinyin_utils import get_pinyin
    
    word_freq = defaultdict(dict)
    
    for filename in os.listdir(input_dir):
        if filename.endswith('.txt'):
            file_path = os.path.join(input_dir, filename)
            with open(file_path, 'r', encoding='utf-8') as f:
                for line in f:
                    line = line.strip()
                    if not line or line.startswith('#'):
                        continue
                    
                    parts = line.split('\t')
                    if len(parts) >= 2:
                        word, freq = parts[0], int(parts[1])
                    else:
                        word, freq = parts[0], 1
                    
                    # 使用jieba分词
                    seg_list = jieba.cut(word)
                    for seg_word in seg_list:
                        if len(seg_word) < 2:
                            continue
                        
                        base_pinyin, fuzzy_pinyins = get_pinyin(seg_word)
                        key = (seg_word, base_pinyin)
                        
                        if key not in word_freq:
                            word_freq[key] = {
                                'freq': 0,
                                'fuzzy': fuzzy_pinyins
                            }
                        word_freq[key]['freq'] += freq
    
    with open(output_file, 'w', encoding='utf-8') as f:
        # 先按词频降序，再按词语拼音升序排序
        sorted_items = sorted(word_freq.items(), key=lambda x: (-x[1]['freq'], x[0][1]))
        for (word, pinyin), data in sorted_items:
            f.write(f'{pinyin}|{word}|{data["freq"]}|{data["fuzzy"]}\n')

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='合并词库文件')
    parser.add_argument('-i', '--input', default='dict', help='输入目录')
    parser.add_argument('-o', '--output', default='merged_dict.txt', help='输出文件')
    args = parser.parse_args()
    
    merge_dicts(args.input, args.output)