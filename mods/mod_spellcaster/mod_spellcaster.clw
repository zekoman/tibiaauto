; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=LifeDialog
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "mod_spellcaster.h"
LastPage=0

ClassCount=9
Class1=CConfigDialog
Class2=CMod_spellcasterApp
Class3=CHealList

ResourceCount=8
Resource1=IDD_HEALLIST (Polish)
Class4=LifeDialog
Resource2=IDD_SUMMON_DIALOG
Resource3=IDD_STRIKE_DIALOG
Class5=ManaDialog
Resource4=IDD_LIFE_DIALOG
Class6=SummonDialog
Resource5=IDD_MANA_DIALOG
Class7=StrikeDialog
Resource6=IDD_AOE_DIALOG
Class8=AOEDialog
Resource7=IDD_CONFIG (Polish)
Class9=TimedDialog
Resource8=IDD_TIMED_DIALOG

[CLS:CConfigDialog]
Type=0
BaseClass=CDialog
HeaderFile=ConfigDialog.h
ImplementationFile=ConfigDialog.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_ENABLE

[CLS:CMod_spellcasterApp]
Type=0
BaseClass=CWinApp
HeaderFile=mod_spellcaster.h
ImplementationFile=mod_spellcaster.cpp
LastObject=CMod_spellcasterApp

[DLG:IDD_CONFIG (Polish)]
Type=1
Class=CConfigDialog
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDC_ENABLE,button,1342246915
Control3=IDC_TOOL_SPELLCASTER_DISABLE_WARNING,button,1342242819
Control4=IDC_TOOL_SPELLCASTER_RANDOM_CAST,button,1342242819
Control5=IDC_TAB1,SysTabControl32,1342177792

[CLS:CHealList]
Type=0
HeaderFile=heallist.h
ImplementationFile=heallist.cpp
BaseClass=CDialog
LastObject=CHealList
Filter=D
VirtualFilter=dWC

[DLG:IDD_HEALLIST (Polish)]
Type=1
Class=CHealList
ControlCount=11
Control1=IDC_HEALLIST_FRAME,button,1342177287
Control2=IDC_HEALLIST_NAME,edit,1350635648
Control3=IDC_HEALLIST_ADD,button,1342242816
Control4=IDC_HEALLIST_DELETE,button,1342242816
Control5=IDOK,button,1342242817
Control6=IDC_HEALLIST_MAX_HP,edit,1350635648
Control7=IDC_STATIC,static,1342308864
Control8=IDC_STATIC,static,1342308864
Control9=IDC_HEALLIST_TRIGGER_HP,edit,1350635648
Control10=IDC_STATIC,static,1342308864
Control11=IDC_HEALLIST_LIST,SysListView32,1350631441

[DLG:IDD_LIFE_DIALOG]
Type=1
Class=LifeDialog
ControlCount=28
Control1=IDC_FRAME_LIFE,button,1342177287
Control2=IDC_TOOL_SPELLCASTER_EXURA_MANA,edit,1350631552
Control3=IDC_TOOL_SPELLCASTER_GRAN_MANA,edit,1350631552
Control4=IDC_TOOL_SPELLCASTER_VITA_MANA,edit,1350631552
Control5=IDC_TOOL_SPELLCASTER_LIFE,button,1342242819
Control6=IDC_STATIC,static,1342308352
Control7=IDC_TOOL_SPELLCASTER_EXURA_LIFE,edit,1350631552
Control8=IDC_TOOL_SPELLCASTER_GRAN_LIFE,edit,1350631552
Control9=IDC_TOOL_SPELLCASTER_VITA_LIFE,edit,1350631552
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308864
Control12=IDC_TOOL_SPELLCASTER_LIFE_SPELL,edit,1350631552
Control13=IDC_TOOL_SPELLCASTER_LIFE_HP,edit,1350631552
Control14=IDC_STATIC,static,1342308864
Control15=IDC_TOOL_SPELLCASTER_LIFE_SPELL_MANA,edit,1350631552
Control16=IDC_TOOL_SPELLCASTER_CUSTOM,button,1342242819
Control17=IDC_TOOL_SPELLCASTER_EXURA,button,1342242819
Control18=IDC_TOOL_SPELLCASTER_GRAN,button,1342242819
Control19=IDC_TOOL_SPELLCASTER_VITA,button,1342242819
Control20=IDC_TOOL_SPELLCASTER_HEAL_PARALYSIS,button,1342242819
Control21=IDC_TOOL_SPELLCASTER_HEAL_POISON,button,1342242819
Control22=IDC_TOOL_SPELLCASTER_MIN_POISON_DAMAGE,edit,1350631552
Control23=IDC_STATIC,static,1342308352
Control24=IDC_TOOL_SPELLCASTER_SIO_MANA,edit,1350631552
Control25=IDC_TOOL_SPELLCASTER_SIO,button,1342242819
Control26=IDC_TOOL_SPELLCASTER_HEAL_LIST,button,1342242816
Control27=IDC_STATIC,static,1342308864
Control28=IDC_TOOL_SPELLCASTER_HEAL_PARALYSIS_ICO,button,1342242819

[CLS:LifeDialog]
Type=0
HeaderFile=LifeDialog.h
ImplementationFile=LifeDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_TOOL_SPELLCASTER_HEAL_PARALYSIS
VirtualFilter=dWC

[DLG:IDD_MANA_DIALOG]
Type=1
Class=ManaDialog
ControlCount=6
Control1=IDC_FRAME_MANA,button,1342177287
Control2=IDC_TOOL_SPELLCASTER_MANA_SPELL,edit,1350631552
Control3=IDC_STATIC,static,1342308864
Control4=IDC_STATIC,static,1342308864
Control5=IDC_TOOL_SPELLCASTER_MANA_MANA,edit,1350631552
Control6=IDC_TOOL_SPELLCASTER_MANA,button,1342242819

[CLS:ManaDialog]
Type=0
HeaderFile=ManaDialog.h
ImplementationFile=ManaDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_FRAME_MANA
VirtualFilter=dWC

[DLG:IDD_SUMMON_DIALOG]
Type=1
Class=SummonDialog
ControlCount=9
Control1=IDC_FRAME_SUMMON_CONTROL,button,1342177287
Control2=IDC_STATIC,static,1342308864
Control3=IDC_TOOL_SPELLCASTER_SUMMON_LESSTHAN,edit,1350631552
Control4=IDC_TOOL_SPELLCASTER_SUMMON_NAME,edit,1350631552
Control5=IDC_STATIC,static,1342308864
Control6=IDC_STATIC,static,1342308864
Control7=IDC_TOOL_SPELLCASTER_SUMMON_MANA,edit,1350631552
Control8=IDC_TOOL_SPELLCASTER_SUMMON,button,1342242819
Control9=IDC_CREATURE_LIST,SysListView32,1350631428

[CLS:SummonDialog]
Type=0
HeaderFile=SummonDialog.h
ImplementationFile=SummonDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_CREATURE_LIST

[DLG:IDD_STRIKE_DIALOG]
Type=1
Class=StrikeDialog
ControlCount=19
Control1=IDC_FRAME_STRIKE_SPELLS,button,1342177287
Control2=IDC_FRAME_MAGE_STRIKE,button,1342177287
Control3=IDC_FRAME_PALADIN_STRIKE,button,1342177287
Control4=IDC_FRAME_KNIGHT_STRIKE,button,1342177287
Control5=IDC_TOOL_SPELLCASTER_STRIKE,button,1342242819
Control6=IDC_TOOL_SPELLCASTER_FLAM,button,1342242819
Control7=IDC_TOOL_SPELLCASTER_FRIGO,button,1342242819
Control8=IDC_TOOL_SPELLCASTER_MORT,button,1342242819
Control9=IDC_TOOL_SPELLCASTER_TERA,button,1342242819
Control10=IDC_TOOL_SPELLCASTER_VIS,button,1342242819
Control11=IDC_STATIC,static,1342308864
Control12=IDC_TOOL_SPELLCASTER_STRIKE_MANA,edit,1350631552
Control13=IDC_STATIC,static,1342308864
Control14=IDC_TOOL_SPELLCASTER_STRIKE_SPELL_DEFAULT,edit,1350631552
Control15=IDC_STATIC,static,1342308864
Control16=IDC_TOOL_SPELLCASTER_STRIKE_SPELL_DEFAULT_HP_MIN,edit,1350631552
Control17=IDC_TOOL_SPELLCASTER_CON,button,1342242819
Control18=IDC_TOOL_SPELLCASTER_SAN,button,1342242819
Control19=IDC_TOOL_SPELLCASTER_HUR,button,1342242819

[CLS:StrikeDialog]
Type=0
HeaderFile=StrikeDialog.h
ImplementationFile=StrikeDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_TOOL_SPELLCASTER_STRIKE

[DLG:IDD_AOE_DIALOG]
Type=1
Class=AOEDialog
ControlCount=22
Control1=IDC_FRAME_AOE_SPELLS,button,1342177287
Control2=IDC_FRAME_KNIGHT_AOE,button,1342177287
Control3=IDC_FRAME_PALADIN_AOE,button,1342177287
Control4=IDC_FRAME_SORCERER_AOE,button,1342177287
Control5=IDC_FRAME_DRUID_AOE,button,1342177287
Control6=IDC_STATIC,static,1342308864
Control7=IDC_TOOL_SPELLCASTER_AOE,button,1342242819
Control8=IDC_TOOL_SPELLCASTER_EXORI,button,1342242819
Control9=IDC_TOOL_SPELLCASTER_EXORI_GRAN,button,1342242819
Control10=IDC_TOOL_SPELLCASTER_EXEVO_MAS_SAN,button,1342242819
Control11=IDC_TOOL_SPELLCASTER_EXEVO_FLAM_HUR,button,1342242819
Control12=IDC_TOOL_SPELLCASTER_EXEVO_VIS_HUR,button,1342242819
Control13=IDC_TOOL_SPELLCASTER_EXEVO_FRIGO_HUR,button,1342242819
Control14=IDC_TOOL_SPELLCASTER_EXEVO_TERA_HUR,button,1342242819
Control15=IDC_TOOL_SPELLCASTER_EXORI_MAS,button,1342242819
Control16=IDC_TOOL_SPELLCASTER_EXEVO_VIS_LUX,button,1342242819
Control17=IDC_TOOL_SPELLCASTER_EXEVO_GRAN_MAS_TERA,button,1342242819
Control18=IDC_TOOL_SPELLCASTER_EXEVO_GRAN_VIS_LUX,button,1342242819
Control19=IDC_TOOL_SPELLCASTER_EXEVO_GRAN_MAS_FLAM,button,1342242819
Control20=IDC_TOOL_SPELLCASTER_EXEVO_GRAN_MAS_VIS,button,1342242819
Control21=IDC_TOOL_SPELLCASTER_EXEVO_GRAN_MAS_FRIGO,button,1342242819
Control22=IDC_TOOL_SPELLCASTER_AOE_AFFECT,edit,1350631552

[CLS:AOEDialog]
Type=0
HeaderFile=AOEDialog.h
ImplementationFile=AOEDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=AOEDialog

[DLG:IDD_TIMED_DIALOG]
Type=1
Class=TimedDialog
ControlCount=13
Control1=IDC_FRAM_TIMED_CASTING,button,1342177287
Control2=IDC_STATIC,static,1342308864
Control3=IDC_TOOL_SPELLCASTER_TIMED_SPELL,edit,1350631552
Control4=IDC_TOOL_SPELLCASTER_TIMED,button,1342242819
Control5=IDC_STATIC,static,1342308864
Control6=IDC_TOOL_SPELLCASTER_TIMED_SPELL_DELAY,edit,1350631552
Control7=IDC_STATIC,static,1342308864
Control8=IDC_TOOL_SPELLCASTER_USE_POTIONS,button,1342242819
Control9=IDC_STATIC,static,1342308864
Control10=IDC_TOOL_SPELLCASTER_TIMED_SPELL_MANA,edit,1350631552
Control11=IDC_TIMED_SPELL_LIST,SysListView32,1350631441
Control12=IDC_TIMED_SPELL_ADD,button,1342242816
Control13=IDC_TIMED_SPELL_DELETE,button,1342242816

[CLS:TimedDialog]
Type=0
HeaderFile=TimedDialog.h
ImplementationFile=TimedDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_TIMED_SPELL_LIST
VirtualFilter=dWC

