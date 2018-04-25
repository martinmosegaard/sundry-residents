# Format JSON

```
~ $ echo '{"key":"value"}' > my.json
~ $ cat my.json
{"key":"value"}
~ $ cat my.json | jq . > tmp.json && rm my.json && mv tmp.json my.json
~ $ cat my.json
{
  "key": "value"
}
```

## If Windows

Use `type` instead of `cat` and `move` instead of `mv`
