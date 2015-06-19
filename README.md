# massws
Mass Web Screenshot Tool - command line based

# Requirements

- QT5
- Windows, Mac OS X or Linux

# Examples 

Take screenshot of web page

```
massws -o screenshot.png http://en.wikipedia.org
```

Take screenshot of web page in 800x600

```
massws -x 800 -y 600 -o screenshot.png http://en.wikipedia.org
```

Take screenshot of list of pages

```
cat list-of-urls.txt | xargs -i massws -x 800 -y 600 {}
```

# Notice 

Due to QT WebKit requirements, GUI is required. Therefore Linux version requires any X11 display 
(it does not use it, but it have to be there!). Mac OS X and Windows are mostly graphical, so 
it is hard to notice.

Therefore, you can use xvfb as dummy X11 display for this tool on headless setups.

# Building 

```
git clone https://github.com/kost/massws.git
cd massws
cd src
qmake
make 
```





