---
title: hexo 图片路径与typora等编辑器的兼容
category:
  - [Tricks]
draft: true
url-root: hexo_image_path_compatible_with_markdown_editor
date: 2023-05-25 16:10:15
tags:
---

## 问题
hexo 博客里的图片资源一般这样解决
```text
-root-dir
--PostXXX
---pic1.png
--PostXXX.md

// PostXXX.md
![image](pic1.png)
```
然后 pic1.png 被引用到同名目录下的图片

问题是，这与我们习惯的markdown 编辑器（typora、vscode 吧啦吧啦）行为不一致

typora要求 相对路径如 **\!\[image](./PostXXX/pic1.png\)**

## 解决
核心在于 处理 post 的context内容

我们按 typora的习惯来，要求 
* image_url = **!\[name](\<prefix\>path\)**
* prefix = \<url-root\>
* url-root = \<title\>

### 1. 文章角注 url-root

更改 hexo-root/scaffolds/post.md
```markdown
---
title: {{ title }}
category: 
    - uncategorized
date: {{ date }}
draft: true
tags:
url-root: {{title}}
---
```

### 2. content内容处理

添加文件 hexo-root/scripts/modify_image_path.js
```js

function escapeRegExp(string) {
    return string.replace(/[.*+?^${}()|[\]\\]/g, "\\$&"); // $& means the whole matched string
}

hexo.extend.filter.register('before_post_render', function (data) {
    if (data.content != undefined && data['url-root'] != undefined){
        // console.log('processing: ',data.path)
        const prefix = '\\.\\/' + escapeRegExp(data['url-root']) + '\\/'
        const reg = new RegExp('!\\[(.*)\\]\\(' + prefix + '(.*)\\)');
        data.content = data.content.replace(reg, '![$1]($2)');
    }
    return data;
});

```

***That's all***