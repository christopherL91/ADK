#Konkordans 📖🔎#
-


##At first when we created our index we was like##

[![Deeper](http://i1.kym-cdn.com/photos/images/facebook/000/531/557/a88.jpg)]()

##But then we were like##

[![Deeper](http://a.abcnews.com/images/Health/HT_sam_griner_then_02_jef_150413_16x9_992.jpg)]()

###Se it in action 😎###

[![asciicast](https://asciinema.org/a/3z9764ywdi65xpncecej8g67f.png)](https://asciinema.org/a/3z9764ywdi65xpncecej8g67f)

###Install notes###

*Requirements:*

* C++11 compatible compiler
* make

```bash
	mkdir -p /var/tmp
	mv file_to_read /var/tmp/
	cd index
	make
	cd ../
	make
	./runutf.sh /var/tmp/file_to_read '/var/tmp/*.idx'
```