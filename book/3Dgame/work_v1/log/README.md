我觉得应该先定义宏, 将 private 在 debug 的模式下变成 public, 在 release 的模式下变成 private.

发现了一个好深的 bug:

parent dirty

set

get

subclass dirty

set

get

如果调用 subclass.Parent:: set, 然后再调用 subclass.Parent:: get, 这时, subclass.get
就会出错, 因为 get 其实 dirty 了

解决方法:
m_dirty 用于记录当前类是否 dirty,m_changed 用于记录是否变化, m_dirty, 由本类来清除,
而 m_changed 由子类来清除 (m_changed , 相当向子类发送信息, 直到子类处理完成)

有点类似中断
