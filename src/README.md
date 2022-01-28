# POI-Analyzer

## 1.Execute

### run directly(recommended)

Click the `POI-Analyzer.exe` in `../build` folder.  Please do **NOT** change or remove other files in the folder.

### build by yourself

Qt version: 6.2.1

Qt Plugins:

- Qt Charts
- Qt WebEngine
- Qt WebChannel

Compiler: MSVC2019 64bit (Please notice that MinGW do **NOT** support Qt webEngine! )

## 2.Using instruction

We have three tabs `USER`, `POI` and `MAP`. 

In `USER` tab, you can do some analysis based on the users you specified. Input the userID to specify the user. If there is more than one user, just split each userID with comma. 

In `POI` tab, you can do analysis based on specified POIs. Similarly, split ID with comma.

In `MAP` tab, you can do analysis based on map. When choose POI analysis, locationID is not need. When choose user trajectory analysis, userID should be specified, and only one userID can be used at a time.

Have fun with it!

