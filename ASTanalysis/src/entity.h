#pragma once
#include <sqlite3.h>
class Relates
{
public:
    std::string namea;
    std::string nameb;
    int type;
    const static std::string createTable;
    // 0- not sure, 1-contain,2-ref

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

const std::string Relates::createTable = "create table if not exists Relates (id integer PRIMARY KEY AUTOINCREMENT, namea text, nameb text, type integer);";

class Structs
{
public:
    std::string name;
    std::string file;
    int extrainfo;
    const static std::string createTable;
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

const std::string Structs::createTable = "create table if not exists structs (id integer PRIMARY KEY AUTOINCREMENT,name text unique, file text, extrainfo integer);";


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
    const static std::string createTable;
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
        res = res + "(\"" + Sname + "\",\"" + Stype + "\",\"" + Sfile + "\"," + std::to_string(extrainfo) + ", \"," + currFile + "\");";
        return res;
    }

};

const std::string GlobalVaribles::createTable = "create table if not exists globalvars(id integer PRIMARY KEY AUTOINCREMENT, name text, type text, file text, extrainfo integer, currfile text);";