#include<bits/stdc++.h>
#include<fstream>
using namespace std;

class doc_element{  // abstract
    public:
    virtual string render()=0;
};
class text_element : public doc_element{
    string text;
    public:
    text_element(string text){
        this->text=text;
    }
    string render() override{
        return text;
    }
};
class image_element : public doc_element{
    string imagepath;
    public:
    image_element(string path){
        this->imagepath=path;
    }
    string render() override{
        return "[image : "+ imagepath + "]";
    }
};

class document{
    vector<doc_element*> elements;
    public:
    void add_element(doc_element *element){
        elements.push_back(element);
    }
    string get_elements(){
        string res="";
        for(auto element:elements){
            res+=element->render() + '\n';
        }
        return res;
    }
};

class persistance{  // // abstract
    public:
    virtual void save(string data)=0;
};
class file_storage : public persistance{
    public:
    void save(string data) override {
        ofstream fout("document.txt");
        if(fout){
            fout<<data;
            fout.close();
            cout<<"data saved to document.txt"<<endl;
        }
        else cout<<"unable to open file for writing"<<endl;
    }
};
class db_storage : public persistance{  
    public:
    void save(string data) override{
        cout<<"data saved to database"<<endl;
    }
};

class doc_render{
    public:
    document *doc;
    doc_render(document *doc){
        this->doc=doc;
    }
    string render(){
        return doc->get_elements();
    }
};

class doc_editor{
    public:
    document *doc;
    doc_editor(document *doc){
        this->doc=doc;
    }
    void addtext(string text){
        doc->add_element(new text_element(text));
    }
    void addimage(string path){
        doc->add_element(new image_element(path));
    }
};


int main(){

    document *Document= new document();
    doc_editor *editor=new doc_editor(Document);
    file_storage *filesaver= new file_storage();
    doc_render *renderer=new doc_render(Document);

    editor->addtext("hello this is first text");
    editor->addtext("hello this is  secon text");
    editor->addimage("picltur.png");

    string data=renderer->render();
    cout<<data<<endl;

    filesaver->save(data);
    editor->addtext("hello this is third text");
    data=renderer->render();
    filesaver->save(data);
    return 0;
    

}
