#include "Load.h"
void Load::Init ( ) {
	std::random_device rd;		//�����_���ϐ�
	std::mt19937 gen ( rd ( ) );		//�����_���ϐ�
	std::uniform_int_distribution<int> distLoad ( 0 , 2 );	//�����_���͈�0�`2
	int randLoad = distLoad ( gen );		//�����_���ϐ�
	//�����_���ǂݍ��߂�悤��
	switch ( randLoad ) {
	case 0:
		Initialize ( L"asset/loading.png" );//�e�N�X�`���^�C�v0��������
		break;
	case 1:
		Initialize ( L"asset/loading1.png" );//�e�N�X�`���^�C�v�P��������
		break;
	case 2:
		Initialize ( L"asset/loading2.png" );//�e�N�X�`���^�C�v�Q��������
		break;
	}
	SetPos ( 0.0f , 0.0f , 0.0f );      //�ʒu��ݒ�
	SetColor ( 1.0f , 1.0f , 1.0f , 1.0f );		//�F��ݒ�
	SetSize ( SCREEN_WIDTH , SCREEN_HEIGHT , 0.0f ); //�傫����ݒ�

}
void Load::Update ( ) {
	input.Update ( );		//�C���v�b�g�X�V
	isLoading = true;		//���[�f�B���O�J�n
	if ( isLoading )
	{
		loadCounter++;		//���[�h�J�E���^�[
		if ( loadCounter >= 60 )	//�P�b�Ԃ�60�t���[��
		{
			//AnyKey��ݒ肵�����ꍇ��Input��AnyKeyTrigger�֐���p�ӂ��Ă��肢���܂�
			if ( GetAsyncKeyState ( VK_SPACE ) )	//�ꉞ�X�y�[�X�L�[��ݒ�
			{
				isLoading = false;	//���[�f�B���O�I��
				nextscene = 1;		//�V�[���̔ԍ��ɒl��������
			}
		}
		scene = nextscene;		//�V�[����؂�ւ�
	}
		return;
}