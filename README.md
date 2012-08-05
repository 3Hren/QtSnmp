QtSnmp. WARNING! This is test readme for myself!
===

SNMP implementation for Qt framework with signal/slot support
---
Why I decided to work on this:
- Because I looked for light-weight implementation of SNMP with asynchronous requests/responses and haven't found it

Usage
---
For example we need to ask information about contact from host 127.0.0.1 asynchronously.
Also we assume there is snmp-agent running on that host. So the code is:

    using namespace QtSnmp;
    ... 
    
    class Foo : public QObject {
      Get *get;
    public:
      Foo(QObject *parent = 0);
      
      void request();
    private:        
      void processResponse();
    };
    
    ...
    
    Foo(QObject *parent) :
      QObject(parent)
    {
      get = new Get("127.0.0.1", "1.3.6.1.2.1.1.4.0", this);
      QObject::connect(get, &Get::responseReceived, &Foo::processResponse);
    }
    
    void Foo::request()
    {      
      get->execute();
    }
    
    void Foo::processResponse()
    {
      if (get->hasErrors()) {
        // Show errors
        return;
      }
        
      QList<Response> responses = get->getResponses();
      for (const Response &response : responses)
        qDebug() << response.getPeer() << response.getObjectId() << response.getType() << response.getValue();      
    }

...