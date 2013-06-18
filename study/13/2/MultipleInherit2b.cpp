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
	C c;

	// �ʲ��Σ��ԤǤ�ξ���Ȥ�ABase�˥��åץ��㥹�Ȥ��Ƥ��뤳�Ȥ�����
	ABase& a1 = static_cast<A1&>(c);
	ABase& a2 = static_cast<A2&>(c);

	a1.AHoge();
	a2.AHoge();
}