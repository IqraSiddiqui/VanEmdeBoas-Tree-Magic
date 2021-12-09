#include "dijsktra_on_VEB.cpp"

int main(){
    int source,destination; //integer variable to hold source and destination
    
    //inputting source node from user whose nearest node is to be found
    cout<<"Enter Source Node: "<<endl;
    cin>>source;
    
    destination=dijsktra_on_VEB(source);//finding nearest node of source by calling dijsktra_on_VEB fnction
    cout << "\nNearest Destination from Source: "<<source<<" is : "<<destination<<endl; //finally printing the output
}
