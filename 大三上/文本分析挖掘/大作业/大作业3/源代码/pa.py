import requests
import urllib.parse

keywords = ["柯南", "路飞", "阿尼亚"]  # 关键词列表

url = 'https://baike.baidu.com/item/'
headers = {
    "User-Agent":"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/75.0.3770.100 Safari/537.36"
}

for keyword in keywords:
    encoded_keyword = urllib.parse.quote(keyword, encoding='utf-8', errors='replace')
    html = requests.get(url + encoded_keyword, headers=headers)
    print(url + encoded_keyword)  # 验证链接是否正确
    html.encoding = html.apparent_encoding
    
    file_path = "C:\\Users\\20848\\Desktop\\" + keyword + ".txt"
    with open(file_path, 'w', encoding='utf-8') as file:
        file.write(html.text)
    
    print("关键词'" + keyword + "'的内容已保存到文件：" + file_path)
