#pragma once

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

    void print() {
        llvm::outs() << Sname << ":" << Stype << ":" << Sfile << "\n";
    }

    std::string genDB()
    {
        std::string res = "insert into globalvars(name, type, file, extrainfo) values ";
        res = res + "(\"" + Sname + "\",\"" + Stype + "\",\"" + Sfile + "\"," + std::to_string(extrainfo) + ");";
        return res;
    }
};