#include "clientImplem.h"
#include <boost/bind.hpp>


ClientImplem::ClientImplem(ClientInfo c_info) :ack_set() {

    //init fields
    service = new io_service() ;
    sock = new ip::udp::socket(*service) ;
    buff = new string(BUFF_SIZE, '\000') ;
    //recieved_updates = new vector<GameUpdate>() ;

    //connect socket
    ip::udp::resolver resolver(*service) ;
    ip::udp::resolver::query query(c_info.serverName, c_info.serverPort) ;
    server_endpoint = *resolver.resolve(query) ;
    if(c_info.localName.compare(""))
    {
        //a local address is provided
        ip::udp::resolver::query query2(c_info.localName,c_info.localPort) ;
        ip::udp::endpoint local_endpoint = *resolver.resolve(query2) ;
        sock->bind(local_endpoint) ;
        sock->open(ip::udp::v4()) ;
    }
    else
    {
        //no local address provided
        sock->open(ip::udp::v4()) ;
        ip::udp::endpoint local_endpoint = sock->local_endpoint() ;
        c_info.localName = local_endpoint.address().to_string();
        int port = local_endpoint.port() ;
        ostringstream os ;
        os << port ;
        c_info.localPort = os.str() ;
    }

    //exchange basic info with server
    //start the network thread
    init_connexion() ;
}

ClientImplem::~ClientImplem(){

    shutdown() ;
    delete service ;
    delete sock ;
    delete buff ;
    //delete recieved_updates ;
}

/*
void ClientImplem::sendEvent(Event &event) {
    string &msg = event.toString() ;
    const ip::udp::endpoint* endp = new ip::udp::endpoint(server_endpoint) ;
    //on_sent will have to free the space occupied by s
    sock->async_send_to(buffer(msg), *endp, boost::bind(&ClientImplem::on_sent,this,msg,_1,_2)) ;
}
*/
/*
vector<GameUpdate>& ClientImplem::recieveUpdates(){

    vector<GameUpdate> *vec = recieved_updates ;
    recieved_updates = new vector<GameUpdate>() ;
    return *vec ;
}

vector<NetEvent> & ClientImplem::recieveNetEvents(){
    return *(new vector<NetEvent>()) ;
}*/

void ClientImplem::on_sent(string & msg, const boost::system::error_code& error, int size){

    if(error != 0)
    {
        //Error occured
        //do some things
        return ;
    }
    if(size != msg.size())
    {
        //The message was not completely transferred --> error stuff
        return ;
    }
    int type = get_msg_type(msg) ;
    switch(type)
    {
    case 0 :
    {
        //Connexion msg
        //Ack expected probably
        int nb = get_msg_nb(msg) ;
        ack_set.insert(nb) ;
        deadline_timer *t = new deadline_timer(*service) ;
        t->expires_from_now(boost::posix_time::millisec(TIME_TO_WAIT)) ;
        t->async_wait(boost::bind(&ClientImplem::check_ack,this, msg, 1,t,_1)) ;
        break ;
    }
    case 1 :
    {
        //Ack nothing to do
        break ;
    }
    case 2 :
    {
        //Event wait for ack
        int nb = get_msg_nb(msg) ;
        ack_set.insert(nb) ;
        deadline_timer *t = new deadline_timer(*service) ;
        t->expires_from_now(boost::posix_time::millisec(TIME_TO_WAIT)) ;
        t->async_wait(boost::bind(&ClientImplem::check_ack,this, msg, 1,t,_1)) ;
        break ;
    }
    case 3 :
    {
        //GameUpdate unliley to happen
        //generate error probably
        break ;
    }
    default :
    {
        //unknown message
        break ;
    }
    } ;
}
/*
void ClientImplem::on_recieve(const boost::system::error_code &error, int size){
    if(error != 0)
    {
        //Error occured during the recieve
        return ;
    }
    int type = get_msg_type(*buff) ;
    switch(type)
    {
    case 0 :
    {
        //Connexion message
        break ;
    }
    case 1 :
    {
        //ack
        int nb = get_msg_nb(*buff) ;
        set<int>::iterator i = ack_set.find(nb) ;
        if(i != ack_set.end())
        {
            ack_set.erase(i);
        }
        break ;
    }
    case 2 :
    {
        //game Event
        break ;
    }
    case 3 :
    {
        //game update
        //see if we pass all the buffer, or only the interesting part
        GameUpdate &gu = GameUpdate::fromString(*buff) ;
        recieved_updates->push_back(gu);
        break ;
    }
    default :
    {
        break ;
    }

    }
}
*/

void ClientImplem::init_connexion(){

    return ;
}

void ClientImplem::shutdown(){

}

void ClientImplem::check_ack(string &msg, int nb_times, deadline_timer *t, const boost::system::error_code &err){
    if(err !=0)
    {
        //Error occured
        return ;
    }
    int nb = get_msg_nb(msg) ;

    if(nb_times >= NB_TRY)
    {
        //Server did not ack
        //Error
        return ;
    }

    if(ack_set.find(nb) != ack_set.end())
    {
        //No Ack recieved
        //resend
        t->expires_from_now(boost::posix_time::millisec(TIME_TO_WAIT)) ;
        //not sure it works...
        sock->async_send(buffer(msg), (void (*)(const boost::system::error_code &, int)) NULL) ;
        t->async_wait(boost::bind(&ClientImplem::check_ack, this, msg, nb_times +1, t, _1)) ;
    }
    else
        return ;
}

int ClientImplem::get_msg_type(string &msg){
    return msg[0] ;
}

int ClientImplem::get_msg_nb(string &msg){
    int i, k ;
    for(i=1 ; i <= 4 ; i++)
    {
        k*= 256 ;
        k+= (int) msg[i] ;
    }
    return k ;
}
