import sys

# import the html page and store in a string
file = open("./index.html")
htmlstr = file.read()
file.close()

# replacing the whitespace
htmlstr = htmlstr.replace(" ", "")

# adding slashes to allow for extra quotations in C++ code
htmlstr = htmlstr.replace('\"', '\\"')

# removing newline chars
htmlstr = htmlstr.replace("\n", "")

# adding some necessary spaces back in
htmlstr = htmlstr.replace("<!DOCTYPEhtml>", "<!DOCTYPE html>")
htmlstr = htmlstr.replace("class", " class")
htmlstr = htmlstr.replace("href", " href")


with open('string.txt', 'w', encoding='utf-8') as genFile:
    genFile.write(htmlstr)