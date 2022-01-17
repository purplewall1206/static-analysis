#pragma once

class Relates
{
public:
    std::string namea;
    std::string nameb;
    int type;
    // 0- not sure, 1-contain,2-ref

    Relates(std::string namea, std::string nameb, int type)
        : namea(namea), nameb(nameb), type(type)
    {
    }

    std::string genRelatedDB()
    {
        std::string res = "insert into related (namea, nameb, type) values ";
        res = res + "\"" + namea + "\", \"" + nameb + "\"," + std::to_string(type) + ");";
        return res;
    }
};

class Structs
{
public:
    std::string name;
    std::string file;
    int extrainfo;
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
    // 0-nothing, 1-pointer, 2-struct,3-array

    GlobalVaribles(std::string Sname, std::string Stype, std::string Sfile)
        : Sname(Sname), Stype(Stype), Sfile(Sfile)
    {
        file = Sfile;
    }

    GlobalVaribles(std::string Sname, std::string Stype, std::string Sfile, int extrainfo)
        : Sname(Sname), Stype(Stype), Sfile(Sfile), extrainfo(extrainfo)
    {
        file = Sfile;
    }

    void print()
    {
        llvm::outs() << Sname << ":" << Stype << ":" << Sfile << "\n";
    }

    std::string genDB()
    {
        std::string res = "insert into globalvars(name, type, file, extrainfo) values ";
        res = res + "(\"" + Sname + "\",\"" + Stype + "\",\"" + Sfile + "\"," + std::to_string(extrainfo) + ");";
        return res;
    }
};