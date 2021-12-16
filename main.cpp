#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <queue>
using namespace std;

/*void ispisiPitanja(vector<string> vektor_pitanja){
    for (int i = 0; i < vektor_pitanja.size(); i++) {
        cout << vektor_pitanja[i] << endl;
    }
}*/

class klasa_stablo {
protected:
    /*string recenica;
    int ocena = 0;
    vector<klasa_stablo*> sinovi;*/
public:
    string recenica;
    int ocena = 0, nivo_cvora=0, pozicija_u_vektoru=0;
    vector<klasa_stablo*> sinovi, pokazivac_na_oca;
    vector<int> ocene_potomaka;

    klasa_stablo dodajOdgovore(klasa_stablo*& koren, string recenica_odgovor) {
        if (koren->sinovi.size() <= 10) {
            klasa_stablo *pokazivac_na_oca= new klasa_stablo;
            klasa_stablo *sinovi= new klasa_stablo;
            sinovi->recenica=recenica_odgovor;
            koren->sinovi.push_back(sinovi);
            ocene_potomaka.push_back(sinovi->ocena);
            if(koren!=nullptr){
            koren->pokazivac_na_oca.push_back(koren); //ti ovde pokazujes na samog sebe
            }
        }
        return *koren;
    }

};

void ispisiPitanja(vector<klasa_stablo> vektor_pitanja){
    for (int i = 0; i < vektor_pitanja.size(); i++) {
        cout <<i<<". "<< vektor_pitanja[i].recenica<< endl;
    }
}

klasa_stablo* pretragaPitanja(vector<klasa_stablo> vektor_pitanja, int n){
    klasa_stablo* pomocno_pitanje=new klasa_stablo;
    *pomocno_pitanje=vektor_pitanja[n];
    return pomocno_pitanje;
}

klasa_stablo* pretragaOdgovora(string question, string answer, vector <klasa_stablo> vektor_pitanja){
    klasa_stablo koren;
    klasa_stablo* next=new klasa_stablo;
    queue<klasa_stablo> node_queue;
    for (int i = 0; i < vektor_pitanja.size(); i++) {
        if (vektor_pitanja[i].recenica==question){
            koren=vektor_pitanja[i];
        }
    }
    *next=koren;
    node_queue.push(*next);
    while(!node_queue.empty()) {
        *next = node_queue.front();
        node_queue.pop();
        if (next->recenica == answer) {
            return next;
        }
        if (!next->sinovi.empty()) {
            for (int i = 0; i < next->sinovi.size(); i++) {
                node_queue.push(*next->sinovi[i]);
            }
        }
    }
}

void povecajOcenuOdgovora(string question, string answer, vector <klasa_stablo> vektor_pitanja){
    klasa_stablo koren;
    for (int i = 0; i < vektor_pitanja.size(); i++) {
        if (vektor_pitanja[i].recenica==question){
            koren=vektor_pitanja[i];
        }
    }
    for (int i = 0; i < koren.sinovi.size(); i++) {
        if (koren.sinovi[i]->recenica == answer){
            koren.sinovi[i]->ocena++;
        }
    }
}

void urediOdgovore(vector <klasa_stablo> vektor_pitanja){
    klasa_stablo koren, next, tmp;
    queue<klasa_stablo> node_queue;

    for (int i = 0; i < vektor_pitanja.size(); i++) {
        koren=vektor_pitanja[i];
        next=koren;
        node_queue.push(next);
        while(!node_queue.empty()) {
            next = node_queue.front();
            node_queue.pop();
            for (int i = 0; i<next.sinovi.size(); i++){
                for (int j = i+1; j < next.sinovi.size(); j++){
                    if(next.sinovi[i]->ocena<next.sinovi[j]->ocena){
                        //swap(next.sinovi[j], next.sinovi[i]); //proveri ako moze swap, ako ne onda samo cepaj sa tmp
                        tmp=*next.sinovi[i];
                        *next.sinovi[i]=*next.sinovi[j];
                        *next.sinovi[j]=tmp;
                    }
                }
            }
            if (!next.sinovi.empty()) {
                for (int i = 0; i < next.sinovi.size(); i++) {
                    node_queue.push(*next.sinovi[i]);
                }
            }
        }
    }
}

void ispisPitanjaIOdgovora(string question, vector <klasa_stablo>& vektor_pitanja){
    klasa_stablo koren, next;
    queue<klasa_stablo> node_queue;
    int nivo=1;
    for (int i = 0; i < vektor_pitanja.size(); i++) {
        if (vektor_pitanja[i].recenica==question){
            koren=vektor_pitanja[i];
        }
    }
    next=koren;
    node_queue.push(next);
    cout<<koren.recenica<<endl;
    while(!node_queue.empty()) {
        next = node_queue.front();
        node_queue.pop();
        for(int i=0; i<next.sinovi.size(); i++){
            for(int j=0; j<=next.sinovi[i]->nivo_cvora; ++j){
                cout<<"  ";
            }
            if(next.sinovi[i]->nivo_cvora==0){
                cout<<i<<"."<<next.sinovi[i]->recenica<<endl;
            }else {
                cout << next.pozicija_u_vektoru <<"."<<i<< "." << next.sinovi[i]->recenica << endl;
            }
        }
        if (!next.sinovi.empty()) {
            nivo++;
            for (int i = 0; i < next.sinovi.size(); i++) {
                for(int j =0; j <next.sinovi[i]->sinovi.size(); j++){
                next.sinovi[i]->sinovi[j]->nivo_cvora=nivo;
                next.sinovi[i]->pozicija_u_vektoru=i;
                }
                node_queue.push(*next.sinovi[i]);
            }
        }
    }
}

void obrisiOdgovoriliKomentar(string question, string answer, vector <klasa_stablo>& vektor_pitanja){
    klasa_stablo* koren = nullptr;
    klasa_stablo* koren_cvora_za_brisanje= nullptr;

    for (int i = 0; i < vektor_pitanja.size(); i++) {
        if (vektor_pitanja[i].recenica==question){
            koren=&vektor_pitanja[i];
        }
    }
    for(int i=0; i<koren->sinovi.size(); i++){
        if(koren->sinovi[i]->recenica==answer){
            koren->sinovi.erase(koren->sinovi.begin()+i);
            return;
        }
    }

    queue<klasa_stablo*> node_queue;

    klasa_stablo* next = koren;

    node_queue.push(next);
    while(!node_queue.empty()) {
        next = node_queue.front();
        node_queue.pop();
        if (next->recenica == answer) {
            koren_cvora_za_brisanje=next->pokazivac_na_oca[0];
            break;
        }
        if (!next->sinovi.empty()) {
            for (int i = 0; i < next->sinovi.size(); i++) {
                node_queue.push(next->sinovi[i]);
            }
        }

    }
    for(int i=0; i<koren_cvora_za_brisanje->sinovi.size(); i++){
        if(koren_cvora_za_brisanje->sinovi[i]->recenica==answer){
            koren_cvora_za_brisanje->sinovi.erase(koren_cvora_za_brisanje->sinovi.begin()+i);
            break;
        }
    }
}

void obrisiPitanje(string question, vector <klasa_stablo> &vektor_pitanja){
    for(int i=0; i<vektor_pitanja.size(); i++){
        if(vektor_pitanja[i].recenica==question){
            vektor_pitanja.erase(vektor_pitanja.begin()+i);
        }
    }
}

void dodajKomentar(string question, string answer, string komentar, vector <klasa_stablo> &vektor_pitanja){
    klasa_stablo* komentar_cvor=new klasa_stablo;
    komentar_cvor->recenica=komentar;

    queue<klasa_stablo*> node_queue;

    int i = 0;
    while (vektor_pitanja[i].recenica != question and i < vektor_pitanja.size())
        ++i;

    klasa_stablo* koren = &vektor_pitanja[i];
    klasa_stablo* next = koren;

    node_queue.push(next);
    while(!node_queue.empty()) {
        next = node_queue.front();
        node_queue.pop();
        if (next->recenica == answer) {
            komentar_cvor->pokazivac_na_oca.push_back(next);
            next->sinovi.push_back(komentar_cvor);
            break;
        }
        if (!next->sinovi.empty()) {
            for (int i = 0; i < next->sinovi.size(); i++) {
                node_queue.push(next->sinovi[i]);
            }
        }
    }
}

klasa_stablo pitanje_najvise_poena(vector <klasa_stablo> vektor_pitanja) {
    klasa_stablo koren, next, koren_sa_najvise_poena;
    queue<klasa_stablo> node_queue;
    vector<klasa_stablo> sinovi_kopija;
    int najvise_poena=0;
    for (int i = 0; i < vektor_pitanja.size(); i++) {
        koren=vektor_pitanja[i];
        next = koren;
        node_queue.push(next);
        while (!node_queue.empty()) {
            next = node_queue.front();
            node_queue.pop();
            if(next.ocena>=najvise_poena){
                najvise_poena=next.ocena;
                koren_sa_najvise_poena=koren;
            }
            if (!next.sinovi.empty()) {
                for (int i = 0; i < next.sinovi.size(); i++) {
                    node_queue.push(*next.sinovi[i]);
                }
            }
        }
    }
    return koren_sa_najvise_poena;
}

int main() {

    int rd_br_pitanja,br_pitanja, izbor_odg_pit, rd_br_odgovora;
    vector<klasa_stablo> pitanja = {};
    string pomocna_recenica,pomocna_recenica2, pitanje_za_pretragu, odgovor_za_pretragu, komentar_za_dodavanje;
    klasa_stablo otac, pomocno_pitanje_najvise_poena;
    klasa_stablo* otac_pomocni= new klasa_stablo;
    klasa_stablo odgovor;
    klasa_stablo* odgovor_pomocni=new klasa_stablo;
    klasa_stablo* proba=new klasa_stablo;
    vector<klasa_stablo*> odgovori = {};
    klasa_stablo* pomocni_cvor;
    //klasa_stablo* otac_pomocni;
    bool kraj=false;
    while(kraj!=true) {
        int izbor;
        cout<<"0. Zavrsi unos"<<endl;
        cout<<"1. Dodaj strukturu"<<endl;
        cout<<"2. Dodaj pitanje"<<endl;
        cout<<"3. Dodaj odgovor"<<endl;
        cout<<"4. Pretraga pitanja"<<endl;
        cout<<"5. Pretraga odgovora"<<endl;
        cout<<"6. Povecaj ocenu nekog odgovora"<<endl;
        cout<<"7. Uredjivanje odgovora po njihovoj oceni"<<endl;
        cout<<"8. Ispis svih pitanja"<<endl;
        cout<<"9. Ispis svih pitanja i odgovora"<<endl;
        cout<<"10. Izbirisi odgovor ili komentar"<<endl; //ova jedina ne radi za sada, isproveravaj upise
        cout<<"11. Izbrisi pitanje"<<endl;
        cout<<"12. Pronadji pitanje ciji odgovor ili komentar imaju najvecu ocenu"<<endl;
        cin>>izbor;
        if(izbor<0 or izbor>12 or isdigit(izbor)==true){
            cout<<"pogresan unos";
            izbor=1;
            break;
        }
        switch (izbor) {
            case 0:
                kraj=true;
                break;
            case 1:
                break;
            case 2:
                cout << "Unesite pitanje"<<endl;
                /*cin>>pomocna_recenica2;
                getline(cin, pomocna_recenica);
                pomocna_recenica=pomocna_recenica2+pomocna_recenica;*/
                cin.ignore();
                getline(cin, pomocna_recenica);
                otac.recenica=pomocna_recenica;
                pitanja.insert(pitanja.end(), 1, otac);
                break;
            case 3:
                cout<<"pritisnite 0 ako zelite da odgovorite na pitanje, 1 ako zelite da odgovorite na odgovor";
                cin>>izbor_odg_pit;
                if(izbor_odg_pit==0){
                    cout<<"izaberite n-to pitanje";
                    cin>>rd_br_pitanja;
                    if(isdigit(rd_br_pitanja)!=false){
                        cout<<"uneli ste string a ne broj"<<endl;
                        break;
                    }
                    if(rd_br_pitanja>pitanja.size()){
                        cout<<"Uneli ste nepostojece pitanje, probajte opet"<<endl;
                        break;
                    }
                    cout<<"unesite odgovor";
                    cin.ignore();
                    getline(cin, pomocna_recenica);
                    *otac_pomocni=pitanja[rd_br_pitanja];
                    pitanja[rd_br_pitanja]=pitanja[rd_br_pitanja].dodajOdgovore(otac_pomocni, pomocna_recenica);
                    break;
                }else if(izbor_odg_pit==1){ // ispitaj da li ovo radi
                    cout<<"unesite pitanje na koje za koje je vezan odgovor"<<endl;
                    cin.ignore();
                    getline(cin, pitanje_za_pretragu);
                    cout<<"unesite odgovor na koji zelite da stavite komentar"<<endl;
                    getline(cin, odgovor_za_pretragu);
                    cout<<"unesite komentar koji hocete da dodate";
                    getline(cin, komentar_za_dodavanje);
                    dodajKomentar(pitanje_za_pretragu, odgovor_za_pretragu, komentar_za_dodavanje, pitanja);
                    break;
                }else{
                    cout<<"Uneli ste nepostojeci unos, probajte opet"<<endl;
                    break;
                }
            case 4:
                cout<<"unesite broj pitanja koje hocete da pretrazite";
                cin>>br_pitanja;
                proba=pretragaPitanja(pitanja, br_pitanja);
                break;
            case 5:
                cout<<"unesite pitanje koji zelite da pretrazite";
                cin.ignore();
                getline(cin, pitanje_za_pretragu);
                cout<<"unesite odgovor koji zelite da pretrazite";
                getline(cin, odgovor_za_pretragu);
                pomocni_cvor=pretragaOdgovora(pitanje_za_pretragu, odgovor_za_pretragu, pitanja); //ovde treba nesto jednako, da vrati tome necemu
                break;
            case 6:
                cout<<"unesite pitanje za koje je povezan odgovor";
                cin.ignore();
                getline(cin, pitanje_za_pretragu);
                cout<<"unesite odgovor za koji zelite da povecate ocenu";
                getline(cin, odgovor_za_pretragu);
                povecajOcenuOdgovora(pitanje_za_pretragu, odgovor_za_pretragu, pitanja);
                break;
            case 7:
                urediOdgovore(pitanja);
                break;
            case 8:
                ispisiPitanja(pitanja);
                break;
            case 9:
                cout<<"unesite pitanje za koje zelite da ispisete stablo";
                cin.ignore();
                getline(cin, pitanje_za_pretragu);
                ispisPitanjaIOdgovora(pitanje_za_pretragu, pitanja);
                break;
            case 10:
                cout<<"unesite pitanje za koji zelite da obrisete odgovor";
                cin.ignore();
                getline(cin, pitanje_za_pretragu);
                cout<<"unesite odgovor koji zelite da obrisete";
                getline(cin, odgovor_za_pretragu);
                obrisiOdgovoriliKomentar(pitanje_za_pretragu, odgovor_za_pretragu, pitanja);
                break;
            case 11:
                cout<<"unesite pitanje koje zelite da izbrisete";
                cin.ignore();
                getline(cin, pitanje_za_pretragu);
                obrisiPitanje(pitanje_za_pretragu, pitanja);
                break;
            case 12:
                pomocno_pitanje_najvise_poena=pitanje_najvise_poena(pitanja);
                break;
            default:
                break;
        }
    }
    //ispisiPitanja(pitanja);
    /*cout<<"unesite broj pitanja za ispis";
    cin>>br_pitanja;
    cout<<br_pitanja<<"."<<pitanja[br_pitanja].recenica<<endl;
    for (int i = 0; i < pitanja[br_pitanja].sinovi.size(); i++) {
        cout <<"    "<<br_pitanja<<"."<<i<<"."<< pitanja[br_pitanja].sinovi[i]->recenica << endl;
    }
    cout<<proba.recenica;*/
    //cout<<pomocni_cvor->recenica;
    //cout<<pomocno_pitanje_najvise_poena.recenica;
    return 0;
}
