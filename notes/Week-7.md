---
date: December 23, 2016
author: Aryaman Arora
title: Week 7
---

# Week 7

## `GET` (requests)

```
GET / HTTP/1.1
Host: www.google.com
...
```

`/` represents the index page, the home page; the default page. The page responds with:

```
HTTP/1.1 200 OK
Content-Type: text/html
```

## Chrome's Inspect Tool

### Network

Chrome has some pretty nifty debugging tools that we can use for looking at HTML and CSS, and other programming languages, that are on a site.

![](images/google-inspector.png)

The *network* tab can be used to see what requests our browser is making. Going to the http://www.facebook.com/ login page results in a whopping 41 packets received. Mine is a bit different because I'm logged in...

![](images/facebook-get.png)

Here's that very first `GET` request:

![](images/first-req.png)

Lots of key-value pairs. The envelopes that are sent back are all HTML!

### Page Source
You can see the page source also, which contains the underlying HTML.

We'll notice lots of `<>` and `</>`, and `<head>` and `<body>`. Remember this?

```html
<!DOCTYPE html>

<html>
    <head>
        <title>hello, world</title>
    </head>
    <body>
        hello, world
    </body>
</html>
```

Looks nice, right? Facebook's is not. This is because whitespace costs data; a spacebar is a byte. If a billion people go to Facebook, that's a billion bytes sent out, a whole gig of data. This "obfuscation" is called **minifying**. Chrome can clean it up in the elements tab.

## `html` Files

If you make an `html` file on your computer, you are the only person that can access it. If you want other people to see it on the internet, you have to use a web server. Cloud9 and GitHub have these for free!

In Cloud9:

```bash
apache50 start .
```

This is how you can have public websites! When you host on CS50 IDE, you get a subdomain of CS50's domain, [cs50.io](http://www.cs50.io).

### Tags
`HTML` is all about tags.

| Tag        | Meaning   |
| :--------- | :-------- |
| `<p>`      | paragraph |
| `<h#>`     | heading   |
| `<ul>`     | unordered list |
| `<ol>`     | ordered list |
| `<li>`     | list item |
| `<img/>`   | image     |
| `<iframe>` | video, page |
| `<div>`    | division |

You can reference local or remote files.

## CSS

**CSS** (Cascading Style Sheets) are used for styling HTMl pages. They can be intermingled in one document, as in `css-0.html`.

CSS is just key value pairs, like so:

```
color: red;
background-color: green;
```

This is where `<style>` tags come in.

```css
body
{
  text-align: center;
  background-color: blue;
}

#top
{
  color: red;
  font-size: 36px;
  font-weight: bold;
}

#middle
{
  font-size: 24px;
}

#bottom
{
  color: blue;
  font-size: 12px;
}
```

This will go in the `<head>`. Or, we can have a separate `.css` file and use `<link>` to include it. This is better design, because it's more flexible.

## Dynamic Sites
Soon, we'll learn PHP!

# Week 7, continued

## PHP

**PHP**! No need for main functions. Here's how you declare variables:

```php
<?php
$var = 32;
$var = "something";
```

PHP is loosely-typed, so no need for `int` or `char`. Here are conditions:

```php
<?php
if (condition) {
  // do this
}
else if (condition) {
  // do this
}
else {
  // do this
}
```

It's the same! Same for booleans:

```php
<?php
if (condition || condition && condition) {
  // do this
}
```

and switches:

```php
<?php
switch (expression) {
  case i:
    // do this
    break;
}
```

and loops:

```php
<?php
for (initialization, condition, iterator) {
  // do this
}

while (condition) {
  // do this
}

do {
  // do this
} while (condition);

foreach ($numbers as $number) {
  // do something with $number, in the array $numbers
}
```

Here's an array, and a fancy new *associative array*!:

```php
<?php
$numbers = [1, 2, 4, 8, 16, 32];
$numbers[1] // 2

// associative arrays!!
$quote = ["symbol" => "FB", "price" => "79.53"];
$quote["symbol"] // "FB"
```

PHP has a **ton** of functions. It's a higher-level language, far beyond C. We don't have to worry about memory management or `malloc()` and stuff.

Furthermore, C is a compiled language; it has to be converted to machine code. PHP is an interpreted language, that an interpreter can understand line by line in source code form.

In PHP, we give up speed for ease of creation. Meaning PHP is significantly slower. For example, `speller.php` takes 1.26 seconds to spell check the King James Bible, and `speller.c` takes 0.56 seconds.

*(psst... remember CSVs? Comma-separated values? Yeah, you should.)*

PHP is object-oriented; variables have methods, just like in Java and Python. We use `->` to access methods.

### Super Global variables

There are a few *super global variables* in PHP. These are like `$_GET` and `$_POST`, and automate accessing form data. For example, if someone has submitted their name,

```php
<?php $_POST["name"] ?>
```
