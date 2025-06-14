<h2>Сборка проекта</h2>

<p>Для сборки проекта выполните следующие шаги:</p>

<ol>
  <li>Клонируйте репозиторий:</li>
</ol>

<pre><code>git clone https://github.com/mustafayevbst/minesweeper.git
cd minesweeper
</code></pre>

<ol start="2">
  <li>Создайте и перейдите в каталог сборки:</li>
</ol>

<pre><code>mkdir build
cd build
</code></pre>

<ol start="3">
  <li>Запустите CMake для генерации файлов сборки:</li>
</ol>

<pre><code>cmake ..
</code></pre>

<ol start="4">
  <li>Соберите проект:</li>
</ol>

<pre><code>cmake --build .
</code></pre>

<p>После успешной сборки исполняемый файл <code>minesweeper.exe</code> появится в каталоге <code>build</code>. Запустите его для начала игры.</p>
