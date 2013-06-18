/*
 * ¿�ŷѾ��ˤĤ���
 * Ʊ�����饹�򣲤İʾ�Ѿ���������ˡ�ˤĤ���
 *
 * ���쥯�饹ABase���Ѱդ���
 * ABase��Ѿ�����A1���饹��ABase��Ѿ�����A2���饹��������ޤ���
 * C���饹�Ǥ�A1��A2���饹��Ѿ����뤳�Ȥˤ�ä�ABase�򣲤ķѾ����뤳�Ȥ��Ǥ��ޤ���
 */
#include<iostream>
using namespace std;

/*
 * ���쥯�饹ABase
 */
class ABase {
	public:
		virtual ~ABase(){}
		virtual void AHoge() = 0;
};

/*
 * ABase��Ѿ�����A1, A2���饹
 */
class A1 : public ABase {
	public:
		virtual void AHoge(){
			cout << "A1::AHoge" << endl;
		}
};

class A2 : public ABase {
	public:
		virtual void AHoge(){
			cout << "A2::AHoge" << endl;
		}
};

/*
 * A1, A2��Ѿ�����C���饹
 */
class C : public A1, public A2 {
};

int main(){

	A1* a1sub;
	C*  csub = new C;
	a1sub = dynamic_cast<A1*>(csub);
	a1sub->AHoge();

}