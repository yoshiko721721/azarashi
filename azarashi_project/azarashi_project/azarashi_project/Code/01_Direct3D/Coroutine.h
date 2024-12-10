#pragma once
#include <iostream>
#include <coroutine>
#include <chrono> 
#include <thread>

//�R���[�`���𗘗p���邽�߂̍\����Coroutine
struct Coroutine {
    //�R���[�`���̎d�g�݂�񋟂���\����promise_type
    struct Promise {
        //�R���[�`���̖߂�l�ƂȂ�I�u�W�F�N�g���\�z���ĕԂ��֐�
        Coroutine get_return_object() {
            return Coroutine{ std::coroutine_handle<promise_type>::from_promise(*this) } ;
        }
        /*�ǂ����awaiter��Ԃ��֐�
          awaiter�̎O�̊֐��iCopilot�Q�Ɓj�F
          1.await_ready():
          �R���[�`�����ꎞ��~���邩�ǂ��������肷��Bfalse��Ԃ��ƈꎞ��~���܂��B
          2.await_suspend():
          �R���[�`�����ꎞ��~�����Ƃ��ɌĂ΂��B
          ���̊֐��́A�R���[�`���̃n���h�����󂯎��A��ōĊJ���邩�A���̂܂܍ĊJ���邩�𐧌䂵�܂��B
          3.await_resume():
          �R���[�`�����ĊJ���ꂽ�Ƃ��ɌĂ΂��B���̊֐��́A�ĊJ��̖߂�l��񋟂��܂��B
          awaiter�͂����̊֐���ʂ��ăR���[�`���̃��C�t�T�C�N�����Ǘ����A�񓯊������̗���𐧌䂵�܂��B
        */
        //�R���[�`����"�ŏ��ɌĂяo������"�ɌĂяo�����ɏ�����߂����ǂ����𐧌䂷��initial_suspend
        std::suspend_always initial_suspend() noexcept { return {}; }
        //�R���[�`����"�I������Ō�̃^�C�~���O"�ŌĂяo�����ɏ�����߂����ǂ����𐧌䂷��final_suspend
        std::suspend_always final_suspend() noexcept { return {}; }
        //"�l����"�ŃR���[�`�����I������Ƃ��ɌĂяo�����R�[���o�b�N
        void return_void() {}
        //"�l�t��"�ŃR���[�`�����I������Ƃ��ɌĂяo�����R�[���o�b�N
        void unhandled_exception() {}
    };
    using promise_type = Promise;
    using handle_type  = std::coroutine_handle<Promise>;

    handle_type handle;

    Coroutine(std::coroutine_handle<Promise> h) : handle(h) {}
    ~Coroutine() {
        if (handle) handle.destroy();
    }

};

