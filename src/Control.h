/**
 * Wenn sich der Code, welcher vond er Fernbedienun gesendet wurde geändetr hat, soll das hier identifiziert werden. 
 * Dazu wid der Code wenn dieser feststellt, in diese Klasse übertragen. Hat sich der Code geändert kann über die Methode hasCodeChanged der Code abgefragt werdn wobei das Flag 
 * zurückgestellt wird.  
 */
class Control{
    public:               
        static void setCode(unsigned long code);
        static bool hasCodeChanged();
    private:
        static unsigned long currentCode;
        static bool codeChanged;
        
};
