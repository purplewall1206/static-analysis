#pragma once
#include <sqlite3.h>
class Relates
{
public:
    std::string namea;
    std::string nameb;
    int type;
    // static std::string createTable;
    // 0- not sure, 1-contain,2-ref，3-function pointer

    Relates(std::string namea, std::string nameb, int type)
        : namea(namea), nameb(nameb), type(type)
    {
    }

    std::string genRelatedDB()
    {
        std::string res = "insert into relates (namea, nameb, type) values ";
        res = res + "(\"" + namea + "\", \"" + nameb + "\"," + std::to_string(type) + ");";
        return res;
    }

};

std::string RelatescreateTable = "create table if not exists Relates (id integer PRIMARY KEY AUTOINCREMENT, namea text, nameb text, type integer, CONSTRAINT individual UNIQUE (namea, nameb));";

class Structs
{
public:
    std::string name;
    std::string file;
    int extrainfo;
    // static std::string createTable;
    // not used
    // std::vector<Relates*> relatedstructs;
    
    Structs(std::string name, std::string file)
        : name(name), file(file)
    {
        extrainfo = 0;
    }
    Structs(std::string name, std::string file, int extrainfo)
        : name(name), file(file), extrainfo(extrainfo)
    {
    }

    std::string genStructsDB()
    {
        std::string res = "insert into structs (name, file, extrainfo) values ";
        res = res + "(\"" + name + "\", \"" + file + "\", " + std::to_string(extrainfo) + ");";
        return res;
    }

};

std::string StructscreateTable = "create table if not exists structs (id integer PRIMARY KEY AUTOINCREMENT,name text , file text, extrainfo integer, CONSTRAINT individual UNIQUE (name,file));";
// const std::string Structs::createTable = "create table if not exists structs (id integer PRIMARY KEY AUTOINCREMENT,name text unique, file text, extrainfo integer);";


class GlobalVaribles
{
private:
    std::string name;
    std::string type;
    bool isPointer;
    bool isStruct;
    std::string file;

public:
    std::string Sname;
    std::string Stype;
    std::string Sfile;
    int extrainfo;
    std::string currFile;
    // static std::string createTable;
    // 0-nothing, 1-pointer, 2-struct,3-array

    GlobalVaribles(std::string Sname, std::string Stype, std::string Sfile)
        : Sname(Sname), Stype(Stype), Sfile(Sfile)
    {
        extrainfo = 0;
        currFile = "";
    }

    GlobalVaribles(std::string Sname, std::string Stype, std::string Sfile, int extrainfo)
        : Sname(Sname), Stype(Stype), Sfile(Sfile), extrainfo(extrainfo)
    {
        currFile = "";
    }

    GlobalVaribles(std::string Sname, std::string Stype, std::string Sfile, int extrainfo, std::string currFile)
        : Sname(Sname), Stype(Stype), Sfile(Sfile), extrainfo(extrainfo), currFile(currFile)
    {
    }

    void print()
    {
        llvm::outs() << Sname << ":" << Stype << ":" << Sfile << "\n";
    }

    std::string genDB()
    {
        std::string res = "insert into globalvars(name, type, file,  extrainfo,currfile) values ";
        res = res + "(\"" + Sname + "\",\"" + Stype + "\",\"" + Sfile + "\"," + std::to_string(extrainfo) + ", \"" + currFile + "\");";
        return res;
    }

};

std::string GlobalVariblescreateTable = "create table if not exists globalvars(id integer PRIMARY KEY AUTOINCREMENT, name text, type text, file text, extrainfo integer, currfile text);";

std::string ParamscreateTable = "CREATE TABLE params (	id	INTEGER,name	TEXT,	type	TEXT,	function	TEXT,	PRIMARY KEY(id AUTOINCREMENT));";
class Param
{
public:
    std::string name;
    std::string type;
    std::string function;
    // std::string file;

    Param(std::string name, std::string type, std::string function) {
        this->name = name;
        this->type = type;
        this->function = function;
        // this->file = file;
    }

    std::string genDB()
    {
        std::string res = "insert into params(name, type, function) values ";
        // res = res + "(\"" + name + "\", \"" + type + "\", \"" + function + "\", \"" + file + "\");";
        res = res + "(\"" + name + "\", \"" + type + "\", \"" + function + "\");";
        return res;
    }
};

std::string FunctionDeclarationscreateTable = "CREATE TABLE functiondeclarations (id	INTEGER,name	TEXT,rettype	TEXT,file	TEXT,CONSTRAINT \"individual\" UNIQUE(\"name\",\"file\",\"rettype\"),PRIMARY KEY(id AUTOINCREMENT));";

class FunctionDeclaration
{
    public:
    std::string name;
    std::string retType;
    std::string file;

    FunctionDeclaration(std::string name, std::string retType, std::string file) {
        this->name = name;
        this->retType = retType;
        this->file = file;
    }

    void print()
    {
        std::cout << name << ":" << retType << ":" << file << std::endl;
    }

    std::string genDB()
    {
        std::string res = "insert into functiondeclarations (name, rettype, file) values ";
        res = res + "(\"" + name + "\", \"" + retType + "\", \"" + file  + "\");";
        return res;
    }
};

std::string FunctionUsescreateTable = "CREATE TABLE functionuses (id	INTEGER,name	TEXT,file	TEXT,	PRIMARY KEY(id AUTOINCREMENT));";

class FunctionUse
{
public:
    std::string name;
    std::string file;

    FunctionUse(std::string name, std::string file) {
        this->name = name;
        this->file = file;
    }

    std::string genDB()
    {
        std::string res = "insert into functionuses (name, file) values ";
        res = res + "(\"" + name + "\", \"" + file + "\")";
        return res;
    }
};