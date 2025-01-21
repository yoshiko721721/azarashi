#include "Fade.h"

//�t�F�[�h�E�C��/�A�E�g���Ԃ����[�_�[�̗v�]�ɂ�蒲�����Ă��肢���܂�

void Fade::Init ( ) {
	Initialize ( L"Asset/pic/Fade.png" );   //�t�F�[�h�������� (�^�����̐}�`�ł���)
	SetPos ( 0.0f , 0.0f , 0.0f );      //�ʒu��ݒ�
	SetColor ( 1.0f , 1.0f , 1.0f , 1.0f );		//�F��ݒ�
	SetSize ( SCREEN_WIDTH , SCREEN_HEIGHT , 0.0f ); //�傫����ݒ�
	fademode = FadeOut;			//�t�F�[�h���[�h��������
	fadeOutCounter = 1.0f;		//�t�F�C�h�E�A�E�g�J�E���g��������
	//�t�F�C�h�E�A�E�g�J�E���g�l�̓t�F�C�h�E�A�E�g���s����b��
	fadeInCounter = 0.0f;			//�t�F�C�h�E�C���J�E���g��������

	a = 1.0f;			//�����x�ϐ���������
}

void Fade::Update ( void )
{
	fadeOutCounter = 1.0f;		//Update���Ƀ��Z�b�g
	fadeInCounter = 0.0f;			//Update���Ƀ��Z�b�g
	switch ( fademode )
	{
	case FadeOut:		//�t�F�C�h���I��
		fadeOutCounter -= 0.0167f;		//fadeOutCounter 1�t���[�����Ƀ}�C�i�X�l
		fadeInCounter += 0.0167f;		//fadeInCounter 1�t���[�����Ƀ}�C�i�X�l
		//�t�F�[�h��ʂ����񂾂񔖂��ȂāA�\�����Ȃ��悤��
		a = fadeOutCounter;
		SetColor ( 1.0f , 1.0f , 1.0f , a );						//�F��ݒ�
		if ( fadeInCounter > 3.0f )					//�t�F�[�h�E�A�E�g����莞�Ԍo��
			//3.0�̓t�F�[�h�E�A�E�g��\�������ʂ̕b���v���X1�b�̌��ʁi���݃t�F�[�h�E�A�E�g��1�b�j
		{
			fadeInCounter = 0.0f;						//fadeInCounter�����Z�b�g
			fademode = FadeIn;					//���[�h�`�F���W
		}
		break;
	case FadeIn:		//�t�F�C�h��\��
		fadeInCounter += 0.0167f;		//1�t���[�����Ƀv���X�l	�i���̐ݒ�͎��s���Ԃ�1�b�j
		//�t�F�[�h�E�A�E�g�I���A�t�F�C�h�E�C�������s����i��ʂ��^�����ɂȂ�j
		a = fadeInCounter;
		SetColor ( 1.0f , 1.0f , 1.0f , a );						//�F��ݒ�

		break;
	}
}