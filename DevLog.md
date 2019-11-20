## 开发日志 :

- 2019/11/16 <br/>
完成 : iterFourier(...) 迭代傅里叶算法 <br/>
问题 : CComplexAmplitude 类声明时没有创建空间，之后将无法通过set等函数创建

- 2019/11/18 <br/>
完成 : getLens(...) 功能开发，获取菲涅尔透镜相位分布<br/>
问题 : OutputArray 的 getMat() 初始化的 Mat 函数无法正确返回计算后的结果
```
void fun(InputArray A, OutputArray B)
{
    Mat H = B.getMat();
    H = ..............;
    // B 的内容不会改变
    // H.copyTO(B);
    // B 的内容才会改变
}
```