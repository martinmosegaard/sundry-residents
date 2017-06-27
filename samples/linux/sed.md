# Sed

Replace inline. This example switches `en0` and `en1` in a file:

```sh
sed --in-place='' 's/en1/somelabel/' some.file
sed --in-place='' 's/en0/en1/' some.file
sed --in-place='' 's/somelabel/en0' some.file
```

See also <https://robots.thoughtbot.com/sed-102-replace-in-place>
