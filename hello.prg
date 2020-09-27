
proc main()
    LOCAL v, i
    //tinyfd_beep()
    //tinyfd_notifyPopup("tiny dialogs","Sample of notify popup","info")

    //? tinyfd_messageBox("tiny dialogs","do you like tiny dialogs?","yesno","question",1)
    *? tinyfd_inputBox("tiny dialogs","ciao")
    //? tinyfd_saveFileDialog("tiny dialogs",,{"*.prg","*.hbp"},"Harbour files")
    //v:=tinyfd_openfiledialog("tiny dialogs",,{"*.prg","*.hbp"},"Harbour files",.t.)
    //if ValType(v)=="A"
    //    ? len(v)
    //    for i:=1 to len(v)
    //        ? v[i]
    //    next
    //else
    //    ? v
    //endif

    *? tinyfd_selectFolderDialog("tiny dialogs")
    v := {0,0,0}
    ? tinyfd_colorChooser("tiny dialogs","#4040C0",@v)
    if ValType(v)=="A"
        ? len(v)
        for i:=1 to len(v)
            ? v[i]
        next
    else
        ? v
    endif
