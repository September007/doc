
# show git-repo root dir
git rev-parse --show-toplevel

# create brand new branch
git checkout –orphan <branch name>

# stop tracing file
git rm -r -n  --cached *version.h

# clone new branch from remote
git fetch origin remote_branch:local_new_branch

# git merge 
git merge another-branch -Xignore-all-space -Xignore-space-change -Xignore-cr-at-eol  -Xrenormalize 

# git found all changed file which just change EOL , note --cached mean this search files in storage cache area
git diff --cached -b --numstat \
| egrep $'^0\t0\t' \
| cut -d$'\t' -f3- \
| tr '\n' ' '

# git remove file from storage cache

git reset HEAD  file

# withdraw blank-changed files
https://stackoverflow.com/questions/13793241/make-git-undo-any-whitespace-only-changes

将 工作区的文件里 非 纯空白符号更改的文件提交到 缓存区
git diff -U0 -w --no-color | git apply --cached --ignore-whitespace --unidiff-zero -

# 分支合并
假设 分支 now, other

git checkout now
git checkout other some_subdir
然后此时暂存区会有更改,如果里边有使你厌烦的纯纯空白的更改或者换行符号的更改，参见之前的命令
```bash
# 取消暂存
git reset --cached 
# 将 工作区的文件里 非 纯空白符号更改的文件提交到 缓存区
git diff -U0 -w --no-color | git apply --cached --ignore-whitespace --unidiff-zero -

# 你可以接着把 工作区里所有余下的文件还原
git checkout .
```

vscode 的diff工具 可以选择忽略空白更改
合并的时候 需要 注意，
* 操作暂存区的时候，只需要查找那种需要被清除出暂存区的更改
* 操作工作区的时候，工作区是 other branch， 原来是 now branch，合并other到now需要的是查找工作区里的 新增代码

# checkout file in another branch
find its sha value
git checkout another-branch
git log that-file
===== choose one commit sha value
git checkout your-branch
git checkout that-commit-sha-val that-file

# remove all local change 
git reset --hard
git clean -xrd