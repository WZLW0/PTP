#!/usr/bin/env python
# coding: utf-8

# In[3]:


import datetime
import json

def update_json_date():
    # 计算前天的日期
    today = datetime.date.today()
    one_day = datetime.timedelta(days=1)
    day_before_yesterday = today - 2 * one_day

    try:
        # 读取JSON文件
        with open('config.json', 'r') as file:
            data = json.load(file)

        # 更新since_date字段
        data['since_date'] = day_before_yesterday.strftime('%Y-%m-%d')

        # 写回修改后的数据到JSON文件
        with open('config.json', 'w') as file:
            json.dump(data, file, indent=4)

    except Exception as e:
        print(f"An error occurred: {e}")
        return 0  # 发生异常，写入失败，返回0

    return 1  # 没有异常，写入成功，返回1

# 调用函数并打印结果
result = update_json_date()
print(result)


# In[ ]:




