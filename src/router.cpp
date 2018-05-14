#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "functions.h"
#include "core/filesystem.h"
#include "settings.h"
#include "../lib/json/json.hpp"


using namespace std;
using namespace filesystem;
using json = nlohmann::json;

namespace routes {

    string getClientJs() {
        return "var Neutralino=function(e){var t={};function o(r){if(t[r])return t[r].exports;var n=t[r]={i:r,l:!1,exports:{}};return e[r].call(n.exports,n,n.exports,o),n.l=!0,n.exports}return o.m=e,o.c=t,o.d=function(e,t,r){o.o(e,t)||Object.defineProperty(e,t,{configurable:!1,enumerable:!0,get:r})},o.r=function(e){Object.defineProperty(e,\"__esModule\",{value:!0})},o.n=function(e){var t=e&&e.__esModule?function(){return e.default}:function(){return e};return o.d(t,\"a\",t),t},o.o=function(e,t){return Object.prototype.hasOwnProperty.call(e,t)},o.p=\"\",o(o.s=2)}([function(e,t){e.exports={ajax:function(e){if(e.url)if(e.type){e.method||(e.method=!0),e.debugLog||(e.debugLog=!1);var t=window.XMLHttpRequest?new XMLHttpRequest:new ActiveXObject(\"Microsoft.XMLHTTP\");t.onreadystatechange=function(){4==t.readyState&&200==t.status?(e.success&&e.success(JSON.parse(t.responseText),t.readyState),1==e.debugLog&&console.log(\"SuccessResponse\"),1==e.debugLog&&console.log(\"Response Data:\"+t.responseText)):4==t.readyState&&(1==e.debugLog&&console.log(\"FailureResponse --\\x3e State:\"+t.readyState+\"Status:\"+t.status),e.errorCallback&&e.errorCallback())},sendString=JSON.stringify(e.data),\"GET\"==e.type&&(t.open(\"GET\",e.url+\"?\"+sendString,e.method),t.send(),1==e.debugLog&&console.log(\"GET fired at:\"+e.url+\"?\"+sendString)),\"POST\"==e.type&&(t.open(\"POST\",e.url,e.method),t.setRequestHeader(\"Content-type\",\"application/x-www-form-urlencoded\"),t.send(sendString),1==e.debugLog&&console.log(\"POST fired at:\"+e.url+\" || Data:\"+sendString))}else 1==e.debugLog&&console.log(\"No Default type (GET/POST) given!\");else 1==e.debugLog&&console.log(\"No Url!\")}}},function(e,t,o){let r=o(0);e.exports={createDirectory:(e,t,o)=>{r.ajax({url:\"/filesystem/createDirectory\",type:\"POST\",data:{name:e},success:function(e){t(e)},errorCallback:()=>{o()}})}}},function(e,t,o){let r=o(1);e.exports={filesystem:r}}]);";
    }
    
    string getFile(string file) {
        ifstream t;
        t.open(file);
        string buffer = "";
        string line;
        while(t){
        getline(t, line);
            buffer += line + "\r\n";
        }
        t.close();
        return buffer;
    }

    string getIndex() {
        return "<html style=\"width: 100%; height: 100%; position: absolute; background-repeat:no-repeat; background-position: center; background-color: black; background-image:url('data:image/png;base64,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')\"></html>";
    }

    pair<string, string> handle(string path, string j) {
        json options = settings::getOptions();
        string appname = options["appname"];
        if(path == "/" +  appname ){
            return make_pair(routes::getFile("app\\index.html"), "text/html");
        }
        else if(path == "/neutralino.js"){
            return make_pair(routes::getClientJs(), "text/javascript");
        }
        else if(path == "/") {
            return make_pair(routes::getIndex(), "text/html");
        }
        else {
            vector<string> portions = functions::split(path, '/');
            if(portions.size() == 3) {
                string module = portions[1];
                string func = portions[2];
                string output = "";
                //cout << module << "."<< func << endl;
                if(filesystem::funcmap.find(module + "." + func) != filesystem::funcmap.end() ){
                    pfunc f = filesystem::funcmap[module + "." + func];
                    output = (*f)(j); 
                }
                else {
                    json o = {{"erorr", module + "." + func + " is not supported"}};
                    output = o.dump();
                }

                return make_pair(output, "application/json");
            }
        }
        return make_pair(path, "application/json");
    }


}