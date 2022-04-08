<?php

namespace Database\Factories;

use Illuminate\Database\Eloquent\Factories\Factory;
use Illuminate\Support\Str;

class TagFactory extends Factory
{

    public function definition()
    {
        return [
            'name'=> Str::random(10),
            'symbol_code'=> Str::random(10),
        ];
    }
}