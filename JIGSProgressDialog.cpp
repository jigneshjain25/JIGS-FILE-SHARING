#include <iostream>

#include "JIGSProgressDialog.h"

JIGSProgressDialog::JIGSProgressDialog():QProgressDialog()
{
    setMaximum(101);
    setAutoClose(false);
}

void JIGSProgressDialog::setProgress(qint64 received)
{
    //if(total==-1) total=received+1;
    std::cout<<received<<" "<<total<<"\n";
    this->setValue(received*100/total);
}

void JIGSProgressDialog::setProgress()
{
    //this->setValue(99.99);
}

void JIGSProgressDialog::setTotal(qint64 total)
{
    this->total=total;
}
