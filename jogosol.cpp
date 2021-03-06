#include "jogosol.h"

#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

Jogosol::Jogosol()
{
    Jogosol::readFuncionarios();

    Jogosol::readAtletas();

    Jogosol::readMedalhas();

    Jogosol::readRecordes();

    Jogosol::readFuncionariosIndisp();


    Modalidade* atletismo = new Modalidade("atletismo");
    modalidades.push_back(atletismo);
    Modalidade* badminton = new Modalidade("badminton");
    modalidades.push_back(badminton);
    Modalidade* canoagem = new Modalidade("canoagem");
    modalidades.push_back(canoagem);
    Modalidade* ciclismo = new Modalidade("ciclismo");
    modalidades.push_back(ciclismo);
    Modalidade* futebol = new Modalidade("futebol");
    modalidades.push_back(futebol);
    Modalidade* ginastica = new Modalidade("ginastica");
    modalidades.push_back(ginastica);
    Modalidade* golfe = new Modalidade("golfe");
    modalidades.push_back(golfe);
    Modalidade* hipismo = new Modalidade("hipismo");
    modalidades.push_back(hipismo);
    Modalidade* judo = new Modalidade("judo");
    modalidades.push_back(judo);
    Modalidade* natacao = new Modalidade("natacao");
    modalidades.push_back(natacao);
    Modalidade* taekwondo = new Modalidade("taekwondo");
    modalidades.push_back(taekwondo);
    Modalidade* tenis = new Modalidade("tenis");
    modalidades.push_back(tenis);
    Modalidade* tenisdemesa = new Modalidade("tenisdemesa");
    modalidades.push_back(tenisdemesa);
    Modalidade* tiro = new Modalidade("tiro");
    modalidades.push_back(tiro);
    Modalidade* triatlo = new Modalidade("triatlo");
    modalidades.push_back(triatlo);
    Modalidade* vela = new Modalidade("vela");
    modalidades.push_back(vela);
}

vector<Modalidade*> Jogosol::modalidades {};

vector<Funcionario> Jogosol::funcionarios {};

vector<Atleta> Jogosol::vatletas {};

map<string,vector<int>> Jogosol::medalhas {};

Recorde notFound = Recorde();

BST<Recorde> Jogosol::recordes(notFound);

priority_queue<Funcionario> Jogosol::fila {};

tabFunc Jogosol::tabela {};

void Jogosol::readFuncionarios()
{
    ifstream file;

    file.open("funcionarios.txt", ios::in);

    while(!file.eof())
    {
        Funcionario f;
        f.input(file);
        funcionarios.push_back(f);
        tabela.insert(f);
    }

    file.close();
}

void Jogosol::readFuncionariosIndisp()
{
    ifstream file;

    file.open("funcionariosserind.txt", ios::in);

    string indisp, servico, nome;

    while(!file.eof())
    {
        getline(file, nome, ';');
        getline(file, servico, ';');
        getline(file, indisp, ';');
        int iindisp = stoi(indisp);
        Funcionario f(nome, servico, iindisp);
        fila.push(f);



    }

    file.close();


}

void Jogosol::readAtletas()
{
    ifstream file;

    file.open("atletas.txt", ios::in);

    while(!file.eof())
    {
        Atleta a;
        a.input(file);
        vatletas.push_back(a);
    }
}

void Jogosol::readMedalhas()
{
    ifstream file;

    file.open("medalhas.txt", ios::in);
    string pais,news;
    int ouro,prata,bronze;
    while(getline(file,news))
    {
        istringstream fileinp(news);
        fileinp >> pais;
        fileinp >> ouro;
        fileinp >> prata;
        fileinp >> bronze;
        vector<int> vint = {ouro,prata,bronze};
        medalhas.insert(pair<string,vector<int>> (pais,vint));
    }
}

void Jogosol::readRecordes(){
    ifstream file;

    file.open("recordes.txt", ios::in);
    string local, atleta;
    Data data;
    string modalidade;
    string competicao;
    while(!file.eof())
    {
        getline(file, modalidade, ';');
        getline(file, competicao, ';');
        getline(file, atleta, ';');
        getline(file, local, ';');
        file >> data;
        file.ignore();

        Recorde r(data, local, atleta, modalidade, competicao);

        recordes.insert(r);
    }
}

bool Jogosol::addFuncionario()
{
    ofstream file;

    file.open("funcionarios.txt", ios::app);

    string nome, funcao, modalidade;
    char sexo;
    Data dataNascimento, dataChegada, dataPartida;
    int passaporte, altura, ranking, custoDiario, peso;

    cout << "Nome: ";
    cin.ignore();
    getline(cin, nome);
    cout << endl << "Sexo (H/M): ";
    cin >> sexo;
    cin.ignore(1000, '\n');
    cout << "Data de nascimento (dd/mm/aaaa): ";
    cin >> dataNascimento;
    cout << "Numero de passaporte: ";
    cin >> passaporte;
    cout << "Funcao: ";
    cin.ignore();
    getline(cin, funcao);
    cout << "Data de chegada (dd/mm/aaaa): ";
    cin >> dataChegada;
    cout << "Data de partida (dd/mm/aaaa): ";
    cin >> dataPartida;
    cout << "Custo diario: ";
    cin >> custoDiario;

    if(to_lower(funcao) == "atleta")
    {
        ofstream filea;

        filea.open(R"(/Users/afonsocaiado/Desktop/FACULDADE/ANO 2 /SEM 1/AEDA/TRABALHO AEDA/TrabalhoAEDAParte1/atletas.txt)", ios::app);

        cout << "Modalidade: ";
        getline(cin, modalidade);
        cout << "Peso (kg): ";
        cin >> peso;
        cout << "Altura (cm):";
        cin >> altura;
        cout << "Ranking: ";
        cin >> ranking;

        Atleta a(nome, sexo, dataNascimento, passaporte, funcao, dataChegada, dataPartida, custoDiario, modalidade, peso, altura, ranking);
        vatletas.push_back(a);

        filea << endl << a;

        filea.close();

        /*
        int n;
        cout << "Numero competicoes em que participa: ";
        cin >> n;
        */
        //falta fazê-lo corresponder a competicao
    }

    else
    {
        Funcionario f(nome, sexo, dataNascimento, passaporte, funcao, dataChegada, dataPartida, custoDiario);
        funcionarios.push_back(f);

        file << endl << f;
    }



    file.close();

    return true;

    //falta verificar erros (que fariam a funcao retornar false)
}

vector<Atleta> Jogosol::getVAtletas()
{
    return vatletas;
}

vector<Funcionario> Jogosol::getFuncionarios()
{
    return funcionarios;
}

vector<Modalidade*> Jogosol::getModalidades()
{
    return modalidades;
}

BST<Recorde> Jogosol::getRecordes()
{
    return recordes;
}

priority_queue<Funcionario> Jogosol::getFuncDisp()
{
    return fila;
}

tabFunc Jogosol::getTabela()
{
    return tabela;
}

void Jogosol::addRecorde() {
    Data dataRec;
    string d;
    stringstream sd;
    string local, atleta, modalidade, competicao;
    cin.ignore();
    cout << "Data (dd/mm/aaaa): ";
    cin >> d; d += ";";
    sd << d;
    sd >> dataRec;
    cin.ignore();
    cout << "Local: ";
    getline(cin, local);
    cout << "Nome do Atleta: ";
    getline(cin, atleta);
    cout << "Modalidade: ";
    getline(cin, modalidade);
    cout << "Competicao: ";
    getline(cin, competicao);

    ofstream file;
    file.open("recordes.txt", ios::app);

    Recorde rec(dataRec, local, atleta, modalidade, competicao);
    Recorde r = recordes.find(rec);
    if(r == notFound){
        recordes.insert(rec);
        file << endl << rec;
    } else {
        recordes.remove(r);
        //E preciso remover esta linha do txt
        recordes.insert(rec);
        file << endl << rec;
    }
    file.close();
}

void Jogosol::viewRecorde() {

    int i = 1;
    cout << endl << "_______________ RECORDES _______________" << endl << "|" << setw(40) << "|" << endl;
    BSTItrLevel<Recorde> it(recordes);
    while(!it.isAtEnd()){
        cout << "|   " <<  i << " - " << it.retrieve().getModalidade() << " - " << it.retrieve().getComp() << setw(31-it.retrieve().getModalidade().size()-it.retrieve().getComp().size()) << "|" << endl;
        it.advance();
        i++;
    }
    cout << "|_______________________________________|" << endl;

    int choice;
    cout << endl << "Selecione o Recorde que quer visualizar: ";
    cin >> choice;

    /*if (!cin.good())
    {
        cout << "Por favor introduza um valor valido";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        recordesMenu();
    }*/
    int ii = 1;
    BSTItrLevel<Recorde> itt(recordes);
    while(ii < choice){
        itt.advance();
        ii++;
    }
    cout << endl << "Modalidade: " << itt.retrieve().getModalidade() << endl;
    cout << "Competicao: " << itt.retrieve().getComp() << endl;
    cout << "Nome do atleta: " << itt.retrieve().getAt() << endl;
    cout << "Local: " << itt.retrieve().getLoc() << endl;
    cout << "Data: " << itt.retrieve().getData() << endl;

}


