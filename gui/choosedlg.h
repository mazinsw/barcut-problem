#ifndef _CHOOSEDLG_H_
#define _CHOOSEDLG_H_
#include "control.h"
#include "strings.h"

enum DialogOptions
{
    dlgOpt_enableSizing = 1,
    dlgOpt_explorer = 2,
    dlgOpt_extensionDifferent = 4,
    dlgOpt_fileMustExist = 8,
    dlgOpt_hideReadOnly = 16,
    dlgOpt_noChangeDir = 32,
    dlgOpt_noNetworkButton = 64,
    dlgOpt_noReadOnlyReturn = 128,
    dlgOpt_pathMustExist = 256,
    dlgOpt_readOnly = 512
};

class CommonDialog: public Object
{
public:
    class Options
    {
    private:
        unsigned long int flags;
        unsigned long int evalEnum(DialogOptions option);
    public:
        Options();
        unsigned long int getFlags();
        Options& operator=(DialogOptions option);
        Options& operator+=(DialogOptions option);
        Options& operator-=(DialogOptions option);
    };
private:
    String title;
    String fileName;
    String initialDir;
    Strings filter;
    Options options;
    Control * owner;
    int filterIndex;
protected:
    void prepare(OPENFILENAME& ofn);
public:
    CommonDialog(Control * owner);
    Control * getOwner();
    void setOwner(Control * owner);
    Strings& getFilter();
    int getFilterIndex();
    void setFilterIndex(int index);
    String getFileName();
    void setFileName(String fileName);
    String getTitle();
    void setTitle(String title);
    String getInitialDir();
    void setInitialDir(String initialDir);
    CommonDialog::Options& getOptions();
    virtual bool execute() = 0;
};

class OpenDialog: public CommonDialog
{
private:
    bool multiSelect;
    Strings files;
    void setFiles(char* szFiles);
public:
    String getClassName();
public:
    OpenDialog();
    OpenDialog(Control * owner);
    void setMultiSelect(bool enable);
    Strings& getFiles();
    bool execute();
};

class SaveDialog: public CommonDialog
{
private:
    String defExt;
public:
    String getClassName();
public:
    SaveDialog();
    SaveDialog(Control * owner);
    String getDefaultExt();
    void setDefaultExt(String defaultExt);
    bool execute();
};    

#endif
