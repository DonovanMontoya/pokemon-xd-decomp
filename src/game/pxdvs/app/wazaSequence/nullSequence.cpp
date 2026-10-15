#include <game/pxdvs/app/wazaSequence/modelSequence.hpp>
#include <libc/stddef.h>
typedef char NullSequenceSize[sizeof(NullSequence)==0x3c?1:-1];
typedef char WazaSequenceSize[sizeof(WazaSequence)==0x30?1:-1];
extern NullSequence* g_Sequences;
void NullSequence::Remove(WazaSequence* waza){
    if(!waza)return;
    WazaSequence* next=waza->next;
    WazaSequence* previous=waza->previous;
    if(next)next->previous=previous;
    if(previous)previous->next=next;
    else wazaList=next;
}
void NullSequence::Add(WazaSequence* waza){
    waza->next=wazaList;
    if(wazaList)wazaList->previous=waza;
    waza->previous=0;
    waza->owner=this;
    wazaList=waza;
}
WazaSequence* NullSequence::GetWaza(u16 move,u16 category)const{
    WazaSequence* waza=wazaList;
    while(waza){if(move==waza->move && category==waza->category)return waza;waza=waza->next;}
    return waza;
}
bool NullSequence::IsActive()const{
    for(WazaSequence* waza=wazaList;waza;waza=waza->next)if(waza->IsActive())return true;
    return false;
}
void NullSequence::Update(f32 step){
    WazaSequence* next;
    WazaSequence* waza=wazaList;
    while(waza){
        next=waza->next;
        if(waza->IsActive() && !waza->Update(step))waza->finished=1;
        waza=next;
    }
    for(waza=wazaList;waza;waza=waza->next)waza->SetRenderCamera((_GScamera*)camera);
}
void NullSequence::FreeAllWaza(){
    WazaSequence* waza=wazaList;
    while(waza){WazaSequence* next=waza->next;delete waza;waza=next;}
    wazaList=0;
}
void NullSequence::SetVisibility(bool value){visible=value;}
void NullSequence::SetScale(GSvec* v){scale.param1=v->param1;scale.param2=v->param2;scale.param3=v->param3;}
void NullSequence::SetRotation(GSvec* v){rotation.param1=v->param1;rotation.param2=v->param2;rotation.param3=v->param3;}
void NullSequence::SetPosition(GSvec* v){position.param1=v->param1;position.param2=v->param2;position.param3=v->param3;}
void NullSequence::GetScale(GSvec* v){v->param1=scale.param1;v->param2=scale.param2;v->param3=scale.param3;}
void NullSequence::GetRotation(GSvec* v){v->param1=rotation.param1;v->param2=rotation.param2;v->param3=rotation.param3;}
void NullSequence::GetPosition(GSvec* v){v->param1=position.param1;v->param2=position.param2;v->param3=position.param3;}
NullSequence::~NullSequence(){
    NullSequence* current=g_Sequences;
    FreeAllWaza();
    if(current){
        if(current==this)g_Sequences=next;
        else {
            while(current->next){
                if(current->next==this){current->next=next;break;}
                current=current->next;
            }
        }
    }
}
NullSequence::NullSequence(){
    id=0;visible=1;failed=0;type=0;
    position.param1=0.0f;position.param2=0.0f;position.param3=0.0f;
    rotation.param1=0.0f;rotation.param2=0.0f;rotation.param3=0.0f;
    scale.param1=1.0f;scale.param2=1.0f;scale.param3=1.0f;
    wazaList=0;camera=0;next=0;
}
NullSequence* New_NullSequence(){
    NullSequence* sequence=new NullSequence;
    if(!sequence)return 0;
    sequence->next=g_Sequences;g_Sequences=sequence;
    return sequence;
}
