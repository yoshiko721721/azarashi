#include "Fade.h"

//�t�F�[�h�E�C��/�A�E�g���Ԃ����[�_�[�̗v�]�ɂ�蒲�����Ă��肢���܂�

void Fade::Init ( ) {
	Initialize ( L"Asset/pic/Logo_Team.png" );   //�w�i��������
	SetPos ( 0.0f , 0.0f , 0.0f );      //�ʒu��ݒ�
	SetColor ( 0.0f , 0.0f , 0.0f , 1.0f );		//�F��ݒ�
	SetSize ( SCREEN_WIDTH , SCREEN_HEIGHT , 0.0f ); //�傫����ݒ�
	fademode = FadeIn;			//�t�F�[�h���[�h��������
	fadeInCounter = 0.0f;			//�t�F�C�h�E�C���J�E���g��������
	fadeOutCounter = 0.25f;		//�t�F�C�h�E�A�E�g�J�E���g��������
	r = 0.0f;			//�FR�ϐ���������
	g = 0.0f;			//�FG�ϐ���������
	b = 0.0f;			//�FB�ϐ���������
	a = 1.0f;			//�����x�ϐ���������
}

void Fade::Update ( void )
{

	switch ( fademode )		
	{
	case FadeIn:		//�t�F�C�h��\��
		fadeInCounter += 0.4f / 60.0f;		//��b��0.4�v���X
		//RGB�������Ƀv���X�ɂ��A�t�F�[�h��ʂ͐^�������猳�X�̗l�q�ɕω�
		r = fadeInCounter;
		g = fadeInCounter;
		b = fadeInCounter;
		SetColor ( r , g , b , a );						//�F��ݒ�
		if ( fadeInCounter>3.0f )					//�t�F�[�h�E�C������莞�Ԍo��
		{
			fademode = FadeOut;					//���[�h�`�F���W
		}
		break;
	case FadeOut:		//�t�F�C�h���I��
		fadeOutCounter-= 0.4f / 60.0f;		//��b��0.4�}�C�i�X
		//�t�F�[�h��ʂ����񂾂񔖂��ȂāA�\�����Ȃ��悤��
		a = fadeOutCounter;
		SetColor ( r , g , b , a );						//�F��ݒ�
		break;
	}
}