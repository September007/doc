
# show git-repo root dir
git rev-parse --show-toplevel

# create brand new branch
git checkout –orphan <branch name>

# stop tracing file
git rm -r -n  --cached *version.h
