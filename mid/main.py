import os
import sqlite3
import requests
from bs4 import BeautifulSoup
import threading

# 创建数据库
def create_database():
    conn = sqlite3.connect('news.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS news
                 (id INTEGER PRIMARY KEY AUTOINCREMENT, 
                 title TEXT, 
                 content TEXT, 
                 url TEXT)''')
    conn.commit()
    conn.close()

# 获取新闻URL
def get_news_urls():
    search_url = 'https://news.google.com/search?q=AI'
    response = requests.get(search_url)
    soup = BeautifulSoup(response.text, 'html.parser')
    
    # 找到所有新闻文章的链接
    links = soup.find_all('a', href=True)
    news_urls = []
    count = 0
    for link in links:
        url = link['href']
        if url.startswith('./articles/') and count < 50:
            news_urls.append('https://news.google.com' + url[1:])
            count += 1
    
    return news_urls

# 下载新闻内容并保存到数据库和文件
def fetch_news(url):
    try:
        response = requests.get(url)
        response.raise_for_status()
        soup = BeautifulSoup(response.text, 'html.parser')
        
        # 这里的选择器可能需要根据具体的新闻网站进行调整
        title = soup.find('h1').get_text()
        content = ' '.join(p.get_text() for p in soup.find_all('p'))
        
        save_news_to_db(title, content, url)
        save_news_to_file(title, content, url)
        print(f'Successfully fetched: {title}')
    except Exception as e:
        print(f'Failed to fetch {url}: {e}')

# 保存新闻到数据库
def save_news_to_db(title, content, url):
    conn = sqlite3.connect('news.db')
    c = conn.cursor()
    c.execute("INSERT INTO news (title, content, url) VALUES (?, ?, ?)", (title, content, url))
    conn.commit()
    conn.close()

# 保存新闻到文件
def save_news_to_file(title, content, url):
    directory = 'NVIDIA_news'
    if not os.path.exists(directory):
        os.makedirs(directory)
    
    # 用标题作为文件名，去除非法字符
    filename = ''.join(e for e in title if e.isalnum()) + '.txt'
    filepath = os.path.join(directory, filename)
    
    with open(filepath, 'w', encoding='utf-8') as file:
        file.write(f"Title: {title}\n")
        file.write(f"URL: {url}\n\n")
        file.write(content)

# 多线程下载新闻
def download_news():
    news_urls = get_news_urls()
    
    threads = []
    for url in news_urls:
        thread = threading.Thread(target=fetch_news, args=(url,))
        thread.start()
        threads.append(thread)

    for thread in threads:
        thread.join()

# 主函数
if __name__ == "__main__":
    create_database()
    download_news()
