#include <hbapi.h>
#include <hbstack.h>
#include "tinyfiledialogs.h"

HB_FUNC( TINYFD_BEEP ) {
    tinyfd_beep();
    hb_ret();
}

HB_FUNC( TINYFD_NOTIFYPOPUP ) {
    tinyfd_notifyPopup(hb_parc(1),hb_parc(2),hb_parc(3));
    hb_ret();
}

HB_FUNC( TINYFD_MESSAGEBOX ) {
    hb_retni(tinyfd_messageBox(hb_parc(1),hb_parc(2),hb_parc(3),hb_parc(4),hb_parni(5)));
}

HB_FUNC( TINYFD_INPUTBOX ) {
    char* retVal = tinyfd_inputBox(hb_parc(1),hb_parc(2),hb_parc(3));
    if(retVal) {
        hb_retc(retVal);
    } else {
        hb_ret();
    }
}

HB_FUNC( TINYFD_SAVEFILEDIALOG ) {
    int nFilter = 0;
    const char **tmp = 0;
    if(HB_ISARRAY(3)) {
        nFilter = hb_parinfa( 3, 0 );
        tmp = malloc(sizeof(char*)*nFilter);
        for(int i=0;i<nFilter;i++) {
            tmp[i] = hb_parvc(3,i+1);
        }
    }
    char* retVal = tinyfd_saveFileDialog(hb_parc(1),hb_parc(2),nFilter,tmp,hb_parc(4));
    if(HB_ISARRAY(3)) {
        free((void*)tmp);
    }
    if(retVal) {
        hb_retc(retVal);
    } else {
        hb_ret();
    }
}

HB_FUNC( TINYFD_OPENFILEDIALOG ) {
    int nFilter = 0;
    const char **tmp = 0;
    if(HB_ISARRAY(3)) {
        nFilter = hb_parinfa( 3, 0 );
        tmp = malloc(sizeof(char*)*nFilter);
        for(int i=0;i<nFilter;i++) {
            tmp[i] = hb_parvc(3,i+1);
        }
    }
    HB_BOOL lMulti = hb_parldef(5,HB_FALSE);
    char* retVal = tinyfd_openFileDialog(hb_parc(1),hb_parc(2),nFilter,tmp,hb_parc(4),lMulti);
    if(HB_ISARRAY(3)) {
        free((void*)tmp);
    }
    if(retVal) {
        if(lMulti) {
            nFilter = 1;
            char *exPtr,*ptr = retVal;
            while((ptr=strchr(ptr,'|')) != NULL) {
                nFilter++;
                ptr++;
            }
            hb_reta(nFilter);
            nFilter = 1;
            exPtr = ptr = retVal;
            while((ptr=strchr(exPtr,'|')) != NULL) {
                *ptr = '\0';
                hb_storvc(exPtr, -1, nFilter );
                nFilter++;
                ptr++;
                exPtr = ptr;
            }
            hb_storvc(exPtr, -1, nFilter);
        } else
            hb_retc(retVal);
    } else {
        hb_ret();
    }
}

HB_FUNC( TINYFD_SELECTFOLDERDIALOG ) {
    hb_retc(tinyfd_selectFolderDialog(hb_parc(1),hb_parc(2)));
}

HB_FUNC( TINYFD_COLORCHOOSER ) {
    unsigned char aDefaultRGB[3] = {0,0,0};
    unsigned char aoResultRGB[3];
    if(HB_ISARRAY(2)) {
        aDefaultRGB[0] = (unsigned char)(hb_parvni(2,1));
        aDefaultRGB[1] = (unsigned char)(hb_parvni(2,2));
        aDefaultRGB[2] = (unsigned char)(hb_parvni(2,3));
    }
    char* ret = tinyfd_colorChooser(hb_parc(1),hb_parc(2),aDefaultRGB,aoResultRGB);
    if(ret && HB_ISBYREF(3)) {
        hb_storvni(aoResultRGB[0],3,1);
        hb_storvni(aoResultRGB[1],3,2);
        hb_storvni(aoResultRGB[2],3,3);
    }
    if(ret)
        hb_retc(ret);
    else
        hb_ret();
}
