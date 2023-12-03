#include "share/ob_thread_mgr.h"
#include "create_table_th.h"

namespace oceanbase {
namespace share {

using namespace oceanbase::rpc::frame;

ObCreateTableTh::ObCreateTableTh()
{
  is_inited_ = false;
}

ObCreateTableTh::~ObCreateTableTh()
{}

int ObCreateTableTh::init(std::function<void()> &func)
{
  int ret = common::OB_SUCCESS;

  if (is_inited_) {
    ret = OB_INIT_TWICE;
    OB_LOG(ERROR, "ObCreateTableTh inited twice");
  } else if (OB_FAIL(TG_CREATE_TENANT(lib::TGDefIDs::CreateTableTh, tg_id_))) {
    OB_LOG(ERROR, "ObCreateTableTh create tenant failed");
  } else {
    is_inited_ = true;
    func_ = func;
  }
//   else if (OB_FAIL(cond_->init(ObWaitEventIds::DEFAULT_COND_WAIT))) {
//     OB_LOG(WARN, "init conditional variable failed", K(ret));
//   }
  return ret;
}

void ObCreateTableTh::destroy()
{
  int ret = OB_SUCCESS;
  if (IS_NOT_INIT) {
    ret = OB_NOT_INIT;
    OB_LOG(ERROR, "ObCreateTableTh not inited.");
  } else {
    is_inited_ = false;
    TG_DESTROY(tg_id_);
  }
}

int ObCreateTableTh::start()
{
  int ret = OB_SUCCESS;
  if (IS_NOT_INIT) {
    ret = OB_NOT_INIT;
    OB_LOG(ERROR, "ObCreateTableTh not inited.");
  } else if (OB_FAIL(TG_SET_RUNNABLE_AND_START(tg_id_, *this))) {
    OB_LOG(ERROR, "failed to start CreateTalbeTh.");
  }
  return ret;
}

void ObCreateTableTh::run1() {
  lib::set_thread_name("CreateTableTh");
  OB_LOG(INFO, "MYTEST: run1");
  func_();
}

int ObCreateTableTh::stop()
{
  int ret = OB_SUCCESS;
  if (IS_NOT_INIT) {
    ret = OB_NOT_INIT;
    OB_LOG(ERROR, "ObCreateTableTh not inited.");
  } else {
    TG_STOP(tg_id_);
  }
  return ret;
}

int ObCreateTableTh::wait()
{
  int ret = OB_SUCCESS;
  if (IS_NOT_INIT) {
    ret = OB_NOT_INIT;
    OB_LOG(ERROR, "ObCreateTableTh not inited.");
  } else {
    TG_WAIT(tg_id_);
  }
  return ret;
}

}
}