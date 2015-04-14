# ofxMultiFboBlur
Keeps FBO blurring at interactive speeds by utilizing a set of incrementally scaled down ofxFboBlur objects, and dynamically blurs and fades between them. 

Requires addons:
[ofxFboBlur](https://github.com/armadillu/ofxFboBlur)
[ofxMask](https://github.com/btparker/ofxMask)

Example:
```
  ofFbo::Settings fboS;
  fboS.width = img.getWidth();
  fboS.height = img.getHeight();
  fboS.internalformat = GL_RGB;
  
  int levels = 5;
  float levelBlurSize = 40.0f;
  
  ofxMultiFboBlur multiFboBlur;  
  multiFboBlur.setup(fboS, levels, levelBlurSize);
```

When drawing this, at blurOffset 0.0f the full resolution image is only drawn, at blur 40.0f the next level (0.5 scaled, 20.0f blur) is only drawn, at blur 20.0f it is a crossfade between the two.

Each additional level is half the resolution of the previous one.

[Image credit](http://www.nasa.gov/content/pushing-the-boundaries-of-propelling-deep-space-missions-0/)
