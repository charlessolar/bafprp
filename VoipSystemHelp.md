# Introduction #

Many hardware systems will produce baf files for various things.  And unfortunately the vendors do not always follow the rules when it comes to the correct format.  This page will detail some tips and tricks needed to get proper data out of weird baf files.


---

**Cedar Point Communications**
The Safari C3's default export format has been reported to include an extra 28 bytes at the start of the file to define the format of the file.  Bafprp will choke on those bytes, so you want to instead choose the streamlined export format when pulling baf files.


---

If you know of more platforms that require some tricks, please post a comment