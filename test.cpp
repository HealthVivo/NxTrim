#include "utilityfunc.h"
#include "matepair.h"

string passed(bool a) {
  if(a)
    return("PASSED");
  else
    return("FAILED");
}

//REALLY BASIC TESTS FOR nxtrim.
int main(int argc,char **argv) {
    int minoverlap=12;
    float sim = 0.85;
    string r;
    string junk = "ACTAGCAGAAAGCGACGAGATGTTAATTTATAAGGTAGGAGCCAGTTTCACGTCTGATGAGCCCATTCCTCACAACCGTGTGTATTTGACGGCAGGGTTACTCGCCAACTACCGCCGGGCATTTTGCGGGGGTAAAATGCACGCCGGTGGCAGTCTATGCGTGAGAAGCTTCTACCGAAATAATTAAGCAAAGGGTCGGAACGTTTTTCGTGTACGGGGAACGATCCTCTATAAAACCAGGTTGTGCGTAACCCAAGAATCTAGGAGTATACACACGAGGGCGTACTAGTCTATAATAGG";
    string adapter1 = "CTGTCTCTTATACACATCT";
    string adapter2 = "AGATGTGTATAAGAGACAG";
    string adapterj = adapter1+adapter2;
    cerr << adapter1 << endl << adapter2 << endl<<adapterj << endl;
    size_t a;

    cerr << "Testing no adapter case." <<endl;
    a = findAdapter(junk,minoverlap,sim,true);
    cerr << a << " " << passed(a==junk.size()) << endl<< endl;


    cerr << "Perfect adapter case." <<endl;
    r=junk.substr(0,10)+adapter1+adapter2+junk.substr(10,30);
    a = findAdapter(r,minoverlap,sim,true);
    cerr << a << " " << passed(a==10) << endl<< endl;


    cerr << "Adapter has substitution error." <<endl;
    r=junk.substr(0,13)+adapter1+adapter2+junk.substr(10,30);
    r[20]='X';
    r[35]='X';
    cerr << r << endl;
    a = findAdapter(r,minoverlap,sim,true);
    cerr << a << " " << passed(a==13) << endl<< endl;


    cerr << "Adapter at start." <<endl;
    r=adapter2.substr(2)+junk.substr(10,30);
    cerr << r << endl;
    a = findAdapter(r,minoverlap,sim,true);
    cerr << a << " " << passed(a==-2-adapter1.size()) << endl<< endl;



    cerr << "Adapter at end." <<endl;
    r=junk.substr(0,30)+adapter1.substr(0,15);
    cerr << r << endl;
    a = findAdapter(r,minoverlap,sim,true);
    cerr << a << " " << passed(a==30) << endl<< endl;

    readPair p;
    pairReader infile("example/r1.fastq.gz","example/r2.fastq.gz");
    while(infile.getPair(p)) {
      cerr << p.r1.notN(0,p.r1.l) << " "  << p.r2.notN(0,p.r2.l) << endl;
      cerr << p.r1.notN(p.r1.l-100,p.r1.l) << " "  << p.r2.notN(p.r2.l-100,p.r2.l) << endl;
      cerr << p.r1.notN(0,10) << " "  << p.r2.notN(0,10) << endl;
    }

    return(0);   
}
