#include "FadeEffect.h"

//�t�F�[�h�E�C��/�A�E�g���Ԃ����[�_�[�̗v�]�ɂ�蒲�����Ă��肢���܂�

void FadeEffect::Init ( ) {
	Initialize ( L"Asset/pic/Logo_Team.png" );   //�w�i��������
	SetPos ( 0.0f , 0.0f , 0.0f );      //�ʒu��ݒ�
	SetColor ( 1.0f , 1.0f , 1.0f , 1.0f );		//�F��ݒ�
	SetSize ( SCREEN_WIDTH , SCREEN_HEIGHT , 0.0f ); //�傫����ݒ�
	fademode = FADEIN;			//�t�F�[�h���[�h��������
	fadeInCounter = 0.0f;			//�t�F�C�h�E�C���J�E���g��������
	fadeOutCounter = 0.0f;//�t�F�C�h�E�A�E�g�J�E���g������
	a = 1.0f;			//�����x�ϐ���������
	isFading = true;
}

bool FadeEffect::Update ( float fadeTime )
{
	if (isFading)
	{
		switch (fademode)
		{
		case FADEIN:		//�t�F�C�h��\��
			fadeInCounter += fadeTime / 60.0f;		//���X�ɓ����x���グ��
			/*r = fadeInCounter;
			g = fadeInCounter;
			b = fadeInCounter;*/
			a -= fadeInCounter;
			SetColor(1.0, 1.0, 1.0, a);						//�F��ݒ�
			if (a < 0.0f)					//�t�F�[�h�E�C������莞�Ԍo��
			{
				//fademode = FadeOut;	//���[�h�`�F���W
				isFading = false;
				fadeInCounter = 0;
				return isFading;
			}
			return isFading;
			break;
		case FADEOUT:		//�t�F�C�h���I��
			fadeOutCounter += fadeTime / 60.0f;		//��b��0.4�}�C�i�X
			//�t�F�[�h��ʂ����񂾂񔖂��ȂāA�\�����Ȃ��悤��
			a += fadeOutCounter;
			SetColor(1.0f, 1.0f, 1.0f, a);
			if (a > 1.0f)					//�t�F�[�h�E�C������莞�Ԍo��
			{
				isFading = false;
				fadeOutCounter = 0;
				return isFading;
			}
			//�F��ݒ�
			return isFading;
			break;

		}
	}

}