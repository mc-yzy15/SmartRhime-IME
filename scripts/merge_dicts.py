import os
import argparse
from collections import defaultdict

def merge_dicts(input_dir, output_file):
    from pypinyin import lazy_pinyin, Style
    import jieba
    
    word_freq = defaultdict(int)
    
    for filename in os.listdir(input_dir):
        if filename.endswith('.txt'):
            with open(os.path.join(input_dir, filename), 'r', encoding='utf-8') as f:
                for line in f:
                    line = line.strip()
                    if line:
                        # 智能分词处理
                        words = jieba.lcut(line.split('\t')[0] if '\t' in line else line)
                        for word in words:
                            # 生成标准拼音和多音字组合
                            base_pinyin = ' '.join(lazy_pinyin(word, style=Style.NORMAL))
                            fuzzy_pinyins = ';'.join({p for p in lazy_pinyin(word, style=Style.NORMAL, heteronym=True, strict=False)})
                            
                            word_freq[(word, base_pinyin)] = {
                                'freq': int(line.split('\t')[1]) if '\t' in line else 1,
                                'fuzzy': fuzzy_pinyins
                            }
    
    with open(output_file, 'w', encoding='utf-8') as f:
        for word, freq in sorted(word_freq.items(), key=lambda x: (-x[1], x[0])):
            f.write(f'{word}\t{freq}\n')

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='合并词库文件')
    parser.add_argument('-i', '--input', default='dict', help='输入目录')
    parser.add_argument('-o', '--output', default='merged_dict.txt', help='输出文件')
    args = parser.parse_args()
    
    merge_dicts(args.input, args.output)