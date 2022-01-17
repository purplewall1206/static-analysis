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

    GlobalVaribles(std::string Sname, std::string Stype, std::string Sfile)
        : Sname(Sname), Stype(Stype), Sfile(Sfile)
    {
        file = Sfile;
    }

    void print() {
        llvm::outs() << Sname << ":" << Stype << ":" << Sfile << "\n";
    }
};