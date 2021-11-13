/**
 * @file test_GarbleFilter.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-16
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef TEST_GARBLEFILTER_H
#define TEST_GARBLEFILTER_H
#include <string.h>
#include "acutest.h"
#include "GarbleFilter.h"
#include "utils.h"

void test_ascii(void){
    char t = 'a';
    TEST_CHECK(str2ascii(t) == 97);
    TEST_CHECK(str2ascii('z') == 122);
    TEST_CHECK(str2ascii('A') == 65);
    TEST_CHECK(str2ascii('Z') == 90);
    TEST_MSG("Got %d", str2ascii(t));
}

void text_occurrence(void){
    char t[2000] = "I have a good day\0";
    occurText oc = init_occurText();

    int len = strlen(t);
    TEST_CHECK(len==17);
    TEST_CHECK(t[len-1] == 'y');
    TEST_CHECK(t[0] == 'I');

    //Get occurrence
    get_region_occurrence(t, &oc, 0, len-1);
    TEST_CHECK(oc.occur[str2ascii('h')] == 1);
    TEST_CHECK(oc.occur[str2ascii('o')] == 2);
    TEST_CHECK(oc.occur[str2ascii('a')] == 3);
    TEST_CHECK(oc.occur[str2ascii('y')] == 1);
    TEST_CHECK(oc.nexceed == 0);
    TEST_CHECK(oc.noccur == 10);

    //Add obs
    add_obs('h', &oc);
    TEST_CHECK(oc.obs[str2ascii('h')] == 1);
    TEST_CHECK(oc.nexceed == 1);
    del_obs('h', &oc);
    TEST_CHECK(oc.obs[str2ascii('h')] == 0);
    TEST_CHECK(oc.nexceed == 0);

    TEST_CHECK(oc.obs[str2ascii('z')] == 0);
    TEST_CHECK(oc.nexceed == 0);
}

void find_garble_text(void){
    char text[2000] = "DSARANDOMTEXTISSOHARD\0";
    char garble[2000] = "RTTX\0";
    int head = -1;
    int tail = -1;
    int h2, t2,h3,t3;
    occurText oc2, oc3;
    occurText oc = init_occurText();
    get_region_occurrence(garble, &oc, 0, strlen(garble)-1);


    bool sat = next_garble_region(text, &tail, &head, strlen(text), &oc);

    //Next garble text
    h2 = head; t2 = tail; oc2 = oc;
    bool sat2 = next_garble_region(text, &t2, &h2, strlen(text), &oc2);

    //No garble text
    h3 = h2; t3 = t2; oc3 = oc2;
    bool sat3 = next_garble_region(text, &t3, &h3, strlen(text), &oc3);

    //TEST
    //PIN
    TEST_CHECK(head==12);
    TEST_CHECK(tail==3);
    TEST_CHECK(h2==19);
    TEST_CHECK(t2==9);
    TEST_CHECK(h3== strlen(text));
    TEST_CHECK(t3 == t2+1);
    TEST_CHECK(text[head]=='T');
    TEST_CHECK(text[tail]=='R');
    TEST_CHECK(text[h2]=='R');
    TEST_CHECK(text[t2]=='T');
    //Observation
    TEST_CHECK(oc.obs[str2ascii('R')]==1);
    TEST_CHECK(oc.obs[str2ascii('T')]==2);
    TEST_CHECK(oc.obs[str2ascii('X')]==1);
    TEST_CHECK(oc2.obs[str2ascii('R')]==1);
    TEST_CHECK(oc2.obs[str2ascii('T')]==2);
    TEST_CHECK(oc2.obs[str2ascii('X')]==1);
    //Valid
    TEST_CHECK(oc.nexceed == oc.noccur);
    TEST_CHECK(oc2.nexceed == oc.noccur);
    TEST_CHECK(oc3.nexceed < oc.noccur);
    TEST_CHECK(sat == true);
    TEST_CHECK(sat2==true);
    TEST_CHECK(sat3 == false);
    //Occurrence
    TEST_CHECK(oc.occur[str2ascii('R')] == 1);   
    TEST_CHECK(oc.occur[str2ascii('T')] == 2);   
    TEST_CHECK(oc.occur[str2ascii('X')] == 1);   
    TEST_CHECK(oc.occur[str2ascii('z')] == 0);
    TEST_CHECK(oc.noccur == 3);

}

void find_leftsmall_garble_text(void){
    char text[2000] = "DSARANDOMTEXTISSOHARD\0";
    char garble[2000] = "RTTX\0";
    int head, tail;
    TEST_CHECK(text[strlen(text)] == '\0');
    bool sat1 = leftist_smallest_garble_region(text, strlen(text), garble, strlen(garble), &tail, &head);


    TEST_CHECK(sat1==true);
    TEST_CHECK(tail == 3);
    TEST_CHECK(head == 12);
}

void find_leftsmall_garble_text2(void){
    char text[2000] = "Nooo\0";
    char garble[2000] = "oo\0";
    int head, tail;

    bool sat1 = leftist_smallest_garble_region(text, strlen(text), garble, strlen(garble), &tail, &head);


    TEST_CHECK(sat1==true);
    TEST_CHECK(tail == 1);
    TEST_CHECK(head == 2);
}

void test_slice_text(void){
    char text[2000] = "NooStevengogogo\0";
    slice_text(text, 1,8, strlen(text));
    TEST_CHECK(strcmp(text, "Ngogogo\0")==0);
    TEST_CHECK(strlen(text)==7);
    TEST_MSG("Got %s", text);
}

void text_garblefilter(void){
    char text[MAX_STR_LEN] = "tReRSfOSagcKrczzcKitRwdeGKgKARKFcRriUfeAzqaecKzRFzaSwqceiaciUfitStSffdewKSigtrOArdwOSOwFRcAdaFgfOFUigcffritcGOaqrqqriiqcgaftwetfeSwGdFgUGfUaigfGgOArifdgcReOftKGSKSwUzAGKffzGAOAfqagiFidrgdAeFGfrcRSdgKUFNwKfORRwSFOwieGdRiRwAOeiASAKgFgKfeddzOiaKcwwefAgfSaqGrzrKGSzfRfOtGzfrtrwKgdfGeiwriSqUrGKgqRGFGttGRaGfSgtrOrKiqidKcFqwrGKcFKKqcggrzOeaRqRceRiwedtrfeRaqeeeggeOKfqrUdAAwdAOAxKFczOfFatrSKgKgggSUrKUwOAeqefwiigArSAcfiaKrFqtKigOUrKzcdqeSAeGRcdGAdOwOittgiGGKRzFidzfwfieKdgwcGcfSqigSrRAKrtrtzSfFtfaFwqcUOSeqGrRFFGURgzfwSdzzaRUKgeztgAgwacAOdKzKARaOrwrdUiOafcrzFKGUwtagFzcKedUqdictadRtdKFwraeOqFefrfFAKOiwgOStOtRaFSzGdzGaigOtrieKKAkFUcfKeAAOAcwdtaGFiqeGfRUzafHgrFcrSRKiKGKcOtzfKRFGGegcrrKfairROezGKwdgRRFfiwAzfcSUKSKcKRrqagKRetGarKwrcafzqRffKacSAeccewGzegzKKeSKwcKqUeRFgAGKfageGFigGQRqdwRgFeGzfricwizORRFKAierFteFiaqKOKietrqiAecgFRiKqdgKarzrAKARrOgczvGcUfGqreUwtqFtgRGwSUdfUAKAqtwqcSOeURgUcqrAtFwwdwOdOGrqretUtaSqaifUScRzUqiSrKAcfzatqRzdwRGeORiagKzpeaAwKwAtGUOiUeOgOfGOwriGiUSFzadUqfGUAKSaAgwfddeOteKSqqKgqgRtq\0";
    char garble[MAX_STR_LEN] = "teRSfSagKczzctRweGgKARFRrifeAzqacFzaSiaUitStSfdegOArdOSOwFRcAdFfOFUigcffritcGOaqrqqriqcattSwGgUGfUaigfGgOAricROftKGSSwzAGGAOAfaiirgAeGfrcRSdgKKORwSOwGdRiRwAOeiASAKgFfeddOiKwweASaqGSzffOtGzftrwKgdferiUrGKgqGFGttRatrOriqidKcFwKqczOeqRRiwedtrfRqegeOKfrdwdOKFczfFarSgKggSUwOAeefwiASAcfiKFqtOUrKzdqeSeAdOittgiGGzFdzfwfiKdwfSigrKrtrtfFtfaFwqcUOeqFFGURgfSdzzaRUetgAgcAOdKzKRaOrwriOfcrzFGUagzcKedUqdctadRtKFwraeOqFefrfFAKwgStRaFzGdGagOtriKKAFUceAOAcwdtaGFiqeGfRUzafgFcRKiKGKctzfKRFGegcrKfarezdgRRFiwAzfcSUKcKRragKReGarKwafzqKcSecewGzScKURFAGKfaFgGRqRgGzriciORFKAierFteFaqKOKetrqiecgFRiKdgKrAAOczGcGqrUwqRGwSUdUAKqtwqeRgqrAtFwwdGrqrUaqaifUSRzUqiSrKAcfzatqRzdwRGRigKzeAKwGUOUeOgOGwiGiUSFzadUqfGAKSaAgwddOteKqqKgqgR\0";
    GarbleTextFilter(text, garble);
    TEST_CHECK(strcmp(text,"tReRSfOSagcKrczzcKitRwdeGKgKARKFcRriUfeAzqaecKzRFzaSwqceiaciUfitStSffdewKSigtrOArdwOSOwFRcAdaFgfOFUigcffritcGOaqrqqriiqcgaftwetfeSwGdFgUGfUaigfGgOArifdgcReOftKGSKSwUzAGKffzGAOAfqagiFidrgdAeFGfrcRSdgKUFNwKfORRwdeOteKSqqKgqgRtq\0")==0);
    TEST_MSG("Got %s", text);
}

#endif