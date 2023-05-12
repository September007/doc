---
categories: 
 - [ CLI ]
title: "Regex"
date: 2023-02-15T10:01:03+08:00
draft: false
include_toc: true
---

## grep regex replace
### perl-regex lookaround
https://learnbyexample.github.io/learn_gnugrep_ripgrep/perl-compatible-regular-expressions.html


Lookarounds helps to create custom anchors and add conditions to a pattern. These assertions are also known as zero-width patterns because they add restrictions similar to anchors and are not part of matched portions (especially helpful with -o option). These can also be used to negate a grouping similar to negated character sets. Lookaround assertions can be added to a pattern in two ways — lookbehind and lookahead. Syntax wise, these two ways are differentiated by adding a < for the lookbehind version. The assertion can be negative (syntax !) or positive (syntax =).


|Syntax |	Lookaround type|
|--|--|
| (?!pattern)	|Negative lookahead|
| (?<!pattern)	|Negative lookbehind|
| (?=pattern)	|Positive lookahead|
| (?<=pattern)	|Positive lookbehind|

```bash
$ # extract whole words only if NOT preceded by : or -
$ # can also use '(?<![:-])\b\w++'
$ echo ':cart<apple-rest;tea' | grep -oP '(?<![:-])\b\w+\b'
apple
tea

$ # note that end of string satisfies the given assertion
$ # 'bazbiz' has two matches as the assertion doesn't consume characters
$ echo 'boz42 bezt5 bazbiz' | grep -ioP 'b.z(?!\d)'
bez
baz
biz

$ # extract digits only if it is followed by ,
$ # note that end of string doesn't qualify as this is positive assertion
$ echo '42 foo-5, baz3; x-83, y-20: f12' | grep -oP '\d+(?=,)'
5
83
$ # extract digits only if it is preceded by - and not followed by ,
$ # note that this would give different results for greedy quantifier
$ echo '42 foo-5, baz3; x-83, y-20: f12' | grep -oP '(?<=-)\d++(?!,)'
20
```
## grep regex match with only print matching

```bash
# print all codeblocks child-project path
cat xxx.workspace |grep -P '(?<=Project filename=")[^"]+' -o
```
