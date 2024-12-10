#pragma once
#include <iostream>
#include <coroutine>
#include <chrono> 
#include <thread>

//コルーチンを利用するための構造体Coroutine
struct Coroutine {
    //コルーチンの仕組みを提供する構造体promise_type
    struct Promise {
        //コルーチンの戻り値となるオブジェクトを構築して返す関数
        Coroutine get_return_object() {
            return Coroutine{ std::coroutine_handle<promise_type>::from_promise(*this) } ;
        }
        /*どちらもawaiterを返す関数
          awaiterの三つの関数（Copilot参照）：
          1.await_ready():
          コルーチンが一時停止するかどうかを決定する。falseを返すと一時停止します。
          2.await_suspend():
          コルーチンが一時停止したときに呼ばれる。
          この関数は、コルーチンのハンドルを受け取り、後で再開するか、そのまま再開するかを制御します。
          3.await_resume():
          コルーチンが再開されたときに呼ばれる。この関数は、再開後の戻り値を提供します。
          awaiterはこれらの関数を通じてコルーチンのライフサイクルを管理し、非同期処理の流れを制御します。
        */
        //コルーチンを"最初に呼び出した時"に呼び出し元に処理を戻すかどうかを制御するinitial_suspend
        std::suspend_always initial_suspend() noexcept { return {}; }
        //コルーチンを"終了する最後のタイミング"で呼び出し元に処理を戻すかどうかを制御するfinal_suspend
        std::suspend_always final_suspend() noexcept { return {}; }
        //"値無し"でコルーチンが終了するときに呼び出されるコールバック
        void return_void() {}
        //"値付き"でコルーチンが終了するときに呼び出されるコールバック
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

