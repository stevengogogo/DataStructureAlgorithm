#include "GarbleFilter.h"


occurText init_occurText(){
    occurText oc;

    for(int i=0;i<N_ASCII_ELEMENT;i++){
        oc.occur[i]=0;
        oc.obs[i] = 0;
    }
    oc.nexceed = 0;
    oc.noccur = 0;
    return oc;
}

void add_obs(char c, occurText* oc){
    int asc = str2ascii(c);
    bool rec = false;
    
    if (oc->obs[asc] >= oc->occur[asc] && oc->occur[asc] >0){
        rec = true;
    }

    ++oc->obs[asc];

    if(oc->obs[asc] >= oc->occur[asc] && oc->occur[asc] >0 && !rec){
        ++oc->nexceed;
    }
}

void del_obs(char c, occurText* oc){
    int asc = str2ascii(c);
    bool rec = false;
    if (oc->obs[asc] < oc->occur[asc] && oc->occur[asc] > 0){
        rec = true;
    }

    if(oc->obs[asc]>0){ --oc->obs[asc];}

    //assert(oc->obs[asc]>=0);
    if(oc->obs[asc] < oc->occur[asc] && oc->occur[asc] > 0 && !rec){
        --oc->nexceed;
    }
}

bool satisfied_obs(occurText oc){
    if(oc.nexceed>=oc.noccur){
        return true;
    }
    else{
        return false;
    }
}


void get_region_occurrence(char* text,occurText* oc, int str, int end){
    int i = str;
    int asc;
    for(int i=str;i<=end;i++){
        asc = str2ascii(text[i]);
        if(oc->occur[asc]==0){++oc->noccur;}
        ++(oc->occur[asc]);
    }
}

bool next_garble_region(char* text, int* tail, int* head, int textlen, occurText* oc){
    //Move one step forward
    if(*tail==textlen-1)
        return 0;
    else if (*tail==-1){
        ++(*tail);
    }
    else{
        del_obs(text[*tail], oc);
        ++(*tail);
    }

    //move head
    //if (*head ==-1){ *head = 0; }
    bool satisfied = satisfied_obs(*oc);
    while(*head < textlen && !satisfied){
        ++(*head);
        add_obs(text[*head], oc);
        satisfied = satisfied_obs(*oc);
    }

    if(!satisfied)
        return false;

    //Move tail
    while(*tail<=*head && satisfied){
        del_obs(text[*tail], oc);
        ++(*tail);
        satisfied = satisfied_obs(*oc);
    }

    //Tail: One step back
    --(*tail);
    add_obs(text[*tail], oc);

    assert(satisfied_obs(*oc) == true);
    return true;
}

bool leftist_smallest_garble_region(char* text, int textlen, char* garble, int garblelen, int* tail, int* head){
    int t=-1;
    int h=-1;
    bool sat;
    int len_ori;
    int len_cur;
    occurText oc = init_occurText();
    
    get_region_occurrence(garble, &oc, 0, garblelen-1);

    sat = next_garble_region(text, &t, &h, textlen, &oc);
    *tail = t; *head = h;//record the region
    
    if(!sat)
        return false;

    while(sat){
        sat = next_garble_region(text, &t, &h, textlen, &oc);
        if(sat){
            len_cur = h - t + 1;
            len_ori = *head - *tail + 1;
            //find smaller region
            if(len_cur<len_ori){ *head = h; *tail = t;}
        }
    }

    return true;
}

void slice_text(char* text, int tail, int head, int textlen){
    int len = head - tail + 1;
    for(int i=head+1;i<=textlen;i++){
        text[i-len] = text[i];
    }
}


void GarbleTextFilter(char* text, char* garble){
    int textlen = strlen(text);
    int garblelen = strlen(garble);
    int tail, head;
    bool sat = leftist_smallest_garble_region(text, textlen, garble, garblelen, &tail, &head);

    if(sat)
        slice_text(text, tail, head, textlen);
}